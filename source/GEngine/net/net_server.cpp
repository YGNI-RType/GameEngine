/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_server
*/

#include "GEngine/net/net_server.hpp"
#include "GEngine/cvar/net.hpp"

#include "GEngine/net/net.hpp"

#include <iostream>

namespace Network {

uint16_t NetServer::start(size_t maxClients, uint16_t currentUnusedPort) {
    // TODO : cloes everything if already initted
    if (m_isRunning)
        return currentUnusedPort;

    m_socketv4 = openSocketTcp(currentUnusedPort, false);
    currentUnusedPort++;
    if (CVar::net_ipv6.getIntValue()) { // check if ipv6 is supported
        m_socketv6 = openSocketTcp(currentUnusedPort, true);
        currentUnusedPort++;
    }

    m_maxClients = maxClients;
    m_isRunning = true;
    return currentUnusedPort;
}

void NetServer::stop(void) {
    m_clients.clear();
    m_isRunning = false;
}

void NetServer::createSets(fd_set &readSet) {
    if (!isRunning())
        return;

    for (const auto &client : m_clients) {
        auto &socket = client->getChannel().getTcpSocket();
        auto eventType = socket.getEventType();

        if (eventType == SocketTCP::EventType::READ)
            socket.setFdSet(readSet);
    }

    m_socketv4.setFdSet(readSet);
    if (CVar::net_ipv6.getIntValue())
        m_socketv6.setFdSet(readSet);
}

void NetServer::respondPingServers(const UDPMessage &msg, SocketUDP &udpsocket, const Address &addr) {
    auto pingReponseMsg = UDPMessage(0, SV_BROADCAST_PING);
    UDPSV_PingResponse data = {.tcpv4Port = m_socketv4.getPort(),
                               .tcpv6Port = CVar::net_ipv6.getIntValue() ? m_socketv6.getPort() : (uint16_t)(-1),
                               .maxPlayers = getMaxClients(),
                               .currentPlayers = getNumClients()};

    pingReponseMsg.writeData<UDPSV_PingResponse>(data);
    udpsocket.send(pingReponseMsg, addr);
}

void NetServer::handleNewClient(SocketTCPMaster &socket) {
    UnknownAddress unkwAddr;
    SocketTCP newSocket = socket.accept(unkwAddr);

    if (getNumClients() >= getMaxClients()) {
        newSocket.socketClose();
        return;
    }

    std::shared_ptr<NetClient> cl;
    auto clientAddrType = unkwAddr.getType();
    if (clientAddrType == AT_IPV4)
        cl = std::make_shared<NetClient>(std::make_unique<AddressV4>(unkwAddr.getV4()), std::move(newSocket),
                                         m_socketUdpV4, NET::getEventManager().getSocketEvent());

    else if (clientAddrType == AT_IPV6)
        cl = std::make_shared<NetClient>(std::make_unique<AddressV6>(unkwAddr.getV6()), std::move(newSocket),
                                         m_socketUdpV6, NET::getEventManager().getSocketEvent());
    else
        return; /* impossible */

    // // std::cout << "SV: New client connected" << std::endl;
    m_clients.push_back(cl);

    auto msg = TCPMessage(SV_INIT_CONNECTON);
    auto &channel = cl->getChannel();

    msg.writeData<TCPSV_ClientInit>(
        {.challenge = channel.getChallenge(),
         .udpPort = clientAddrType == AT_IPV6 ? m_socketUdpV6.getPort() : m_socketUdpV4.getPort()});

    // // std::cout << "SV: Client challange: " << channel.getChallenge() << std::endl;

    NET::getEventManager().invokeCallbacks(Event::CT_OnClientConnect, cl);
    channel.sendStream(msg);
}

bool NetServer::handleUDPEvent(SocketUDP &socket, UDPMessage &msg, const Address &addr) {
    if (!isRunning())
        return false;

    switch (msg.getType()) {
    case CL_BROADCAST_PING:
        respondPingServers(msg, socket, addr);
        return true;
    default:
        return handleUdpMessageClients(socket, msg, addr);
    }
}

bool NetServer::handleUdpMessageClients(SocketUDP &socket, UDPMessage &msg, const Address &addr) {
    for (const auto &client : m_clients) {
        auto &channel = client->getChannel();
        if (channel.getAddressUDP() != addr)
            continue;

        client->handleClientDatagram(msg);
        return true;
    }
    return false;
}

bool NetServer::handleTCPEvent(fd_set &readSet) {
    if (!isRunning())
        return false;

    if (m_socketv4.isFdSet(readSet)) {
        handleNewClient(m_socketv4);
        return true;
    }

    if (CVar::net_ipv6.getIntValue() && m_socketv6.isFdSet(readSet)) {
        handleNewClient(m_socketv6);
        return true;
    }

    for (const auto &client : m_clients)
        if (client->handleTCPEvents(readSet)) {
            if (client->isDisconnected()) {
                NET::getEventManager().invokeCallbacks(Event::CT_OnClientDisconnect, client.get());
                m_clients.erase(std::remove_if(m_clients.begin(), m_clients.end(),
                                               [&client](const std::shared_ptr<NetClient> &cl) {
                                                   return cl.get() == client.get();
                                               }),
                                m_clients.end());
            }
            return true;
        }

    return false;
}

bool NetServer::sendPackets(void) {
    if (!isRunning())
        return false;

    for (const auto &client : m_clients)
        client->sendPackets();
    return true;
}

void NetServer::sendToAllClients(UDPMessage &msg) {
    for (const auto &client : m_clients)
        client->sendDatagram(msg);
}

void NetServer::sendToClient(NetClient &client, UDPMessage &msg) {
    if (client.isDisconnected())
        return;

    client.sendDatagram(msg);
}

} // namespace Network
