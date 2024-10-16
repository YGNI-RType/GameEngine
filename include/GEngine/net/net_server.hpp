/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_server
*/

#pragma once

#include "events/socket_event.hpp"
#include "net_client.hpp"
#include "net_socket.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace Network {
class NetServer {
public:
    NetServer(SocketUDP &socketUdpV4, SocketUDP &socketUdpV6)
        : m_socketUdpV4(socketUdpV4)
        , m_socketUdpV6(socketUdpV6) {};
    /* todo : add to support loopback client for listen servers */
    ~NetServer() = default;

    uint16_t start(size_t maxClients, const std::vector<IP> &g_localIPs, uint16_t currentUnusedPort);
    uint16_t start(size_t maxClients, uint16_t currentUnusedPort);
    void stop(void);

    void createSets(fd_set &readSet);

    bool handleTCPEvent(fd_set &readSet);
    bool handleUDPEvent(SocketUDP &socket, UDPMessage &msg, const Address &addr);

    const SocketTCPMaster &getSocketV4(void) const {
        return m_socketv4;
    }
    const SocketTCPMaster &getSocketV6(void) const {
        return m_socketv6;
    }

    uint32_t getNumClients(void) const {
        return m_clients.size();
    }
    uint32_t getMaxClients(void) const {
        return m_maxClients;
    };

    bool isRunning(void) const {
        return m_isRunning;
    }

    void handleNewClient(SocketTCPMaster &socket);

    void respondPingServers(const UDPMessage &msg, SocketUDP &udpsocket, const Address &addr);
    bool handleUdpMessageClients(SocketUDP &socket, UDPMessage &msg, const Address &addr);

    bool sendPackets(void);
    void sendToAllClients(UDPMessage &msg);
    void sendToClient(NetClient &client, UDPMessage &msg);

private:
    bool m_isRunning = false;

    SocketTCPMaster m_socketv4;
    SocketTCPMaster m_socketv6;

    SocketUDP &m_socketUdpV4;
    SocketUDP &m_socketUdpV6;

    size_t m_maxClients;
    std::vector<std::shared_ptr<NetClient>> m_clients;
};

} // namespace Network
