/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_client
*/

#include "GEngine/net/net_client.hpp"
#include "GEngine/net/net.hpp"

#include <algorithm>

// temp
#include <iostream>

namespace Network {
NetClient::NetClient(std::unique_ptr<Address> addr, SocketTCP &&socket, SocketUDP &socketudp,
                     Event::SocketEvent &socketEvent)
    : m_channel(true, std::move(addr), std::move(socket))
    , m_socketUdp(socketudp)
    , m_packOutData(socketEvent)
    , m_packOutDataAck(socketEvent)
    , m_packInData(socketEvent) {
}

void NetClient::sendStream(const TCPMessage &msg) {
    if (!m_channel.isEnabled())
        return;

    m_channel.sendStream(msg);
}

bool NetClient::sendDatagram(UDPMessage &msg) {
    if (!m_channel.isEnabled())
        return false;

    return m_channel.sendDatagram(m_socketUdp, msg);
}

bool NetClient::handleClientStream(void) {
    TCPMessage msg(0);

    if (!m_channel.readStream(msg))
        return false;

    if (m_channel.isDisconnected())
        return true;

    switch (msg.getType()) {
    case CL_CONNECT_INFORMATION: {
        TCPCL_ConnectInformation recvData;
        msg.readData<TCPCL_ConnectInformation>(recvData);

        m_channel.createUdpAddress(recvData.udpPort);

        NET::getEventManager().invokeCallbacks(Event::CT_OnClientReady, this);

        auto msg = TCPMessage(SV_YOU_ARE_READY);
        m_channel.sendStream(msg);
        return true;
    }
    default:
        // std::cout << "SV: client just sent TCP specific message" << std::endl;
        return false;
    }
    return true;
}

bool NetClient::handleClientDatagram(SocketUDP &socket, UDPMessage &msg) {
    size_t readOffset = 0;

    if (!m_channel.isUDPEnabled() || !m_channel.readDatagram(socket, msg, readOffset))
        return false;

    if (msg.shouldAck())
        // std::cout << "SV: client just sent UDP specific message" << std::endl;
        switch (msg.getType()) {
        default:
            return pushIncommingData(msg, readOffset);
        }
    return false;
}

bool NetClient::handleTCPEvents(fd_set &readSet) {
    auto &socket = m_channel.getTcpSocket();
    if (!socket.isFdSet(readSet))
        return false;

    return handleClientStream();
}

/** Net Queue **/

bool NetClient::pushData(const UDPMessage &msg, bool shouldAck) {
    if (shouldAck)
        return m_packOutDataAck.push(msg, 0);
    return m_packOutData.push(msg, 0);
}

bool NetClient::popIncommingData(UDPMessage &msg, size_t &readCount) {
    return m_packInData.pop(msg, readCount, msg.getType());
}

bool NetClient::retrieveWantedOutgoingData(UDPMessage &msg, size_t &readCount) {
    return m_packOutData.pop(msg, readCount);
}

bool NetClient::retrieveWantedOutgoingDataAck(UDPMessage &msg, size_t &readCount) {
    return m_packOutDataAck.pop(msg, readCount);
}

bool NetClient::pushIncommingData(const UDPMessage &msg, size_t readCount) {
    return m_packInData.push(msg, readCount);
}

/***************/

bool NetClient::sendPackets(void) {
    if (isDisconnected() || !m_channel.isEnabled())
        return false;

    size_t byteSent = 0;
    std::vector<bool (Network::NetClient::*)(Network::UDPMessage &, size_t &)> vecFuncs = {
        &NetClient::retrieveWantedOutgoingData, &NetClient::retrieveWantedOutgoingDataAck};

    while (!vecFuncs.empty() || byteSent < m_maxRate) {
        size_t readCount;
        UDPMessage msg(0, 0);
        auto retrieveFunc = vecFuncs.front();
        if (!(this->*retrieveFunc)(msg, readCount)) {
            vecFuncs.erase(vecFuncs.begin());
            continue;
        }

        size_t size = msg.getSize();
        if (!sendDatagram(msg))
            return false; /* how */
        std::rotate(vecFuncs.begin(), vecFuncs.begin() + 1, vecFuncs.end());
        byteSent += size;
    }
    return true;
}

} // namespace Network
