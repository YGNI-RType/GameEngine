/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** socket
*/

#pragma once

#include "msg.hpp"
#include "net_address.hpp"
#include "net_common.hpp"

#include <cstdint>
#include <string>
#include <utility>

#ifndef _WIN32
#include <netinet/in.h> // Add this line to include the header file that defines sockaddr_in
#include <sys/socket.h>
#include <sys/types.h>
#endif

#ifndef _WIN32
typedef int SOCKET;
#endif

namespace Network {

#define UDP_SO_RCVBUF_SIZE 131072

////////////////////////////////////////

class ASocket {

public:
#ifdef _WIN32
    static WSADATA winsockdata;
#endif

    static SOCKET getHighestSocket(void) {
        return m_highFd;
    }

    SOCKET getSocket(void) const {
        return m_sock;
    }

public:
    static void initLibs(void);

    ASocket(const ASocket &other) = delete;
    ASocket &operator=(const ASocket &other) = delete;
    ASocket(ASocket &&other);
    ASocket &operator=(ASocket &&other);

protected:
    ASocket() = default;

    static void addSocketPool(SOCKET socket);
    static void translateAutomaticAddressing(struct sockaddr_storage &addr, uint16_t port, bool ipv6);

    virtual ~ASocket();

private:
    static fd_set m_fdSet;
    static SOCKET m_highFd;

public:
    void setBlocking(bool blocking);
    bool isBlocking(void) const;

    int socketClose(void);

    uint16_t getPort(void) const {
        return m_port;
    }
    bool isFdSet(fd_set &set) const {
        return FD_ISSET(m_sock, &set);
    }
    void setFdSet(fd_set &set) const {
        FD_SET(m_sock, &set);
    }
    void removeFdSet(fd_set &set) const {
        FD_CLR(m_sock, &set);
    }

protected:
    SOCKET m_sock = -1;
    uint16_t m_port = -1;
};

////////////////////////////////////////

class SocketUDP : public ASocket {
public:
    SocketUDP() = default;
    SocketUDP(const IP &ip, uint16_t port, bool block = false);
    SocketUDP(uint16_t port, bool ipv6, bool block = false);

    SocketUDP(const SocketUDP &other) = delete;
    SocketUDP &operator=(const SocketUDP &) = delete;
    SocketUDP(SocketUDP &&other);
    SocketUDP &operator=(SocketUDP &&other);

    ~SocketUDP() = default;

    void init(bool block, uint16_t port);

    /* return the nb bytes sent */
    size_t send(const UDPMessage &msg, const Address &addr) const;

    /* this seems redundant, but to avoid any heap calls, this is necessary */
    bool receiveV4(UDPMessage &msg, AddressV4 &ip) const;
    bool receiveV6(UDPMessage &msg, AddressV6 &ip) const;

private:
    bool receive(struct sockaddr *addr, UDPSerializedMessage &sMsg, socklen_t *len) const;
};

////////////////////////////////////////

class SocketTCP;

class SocketTCPMaster : public ASocket {
public:
    SocketTCPMaster() = default;
    SocketTCPMaster(const IP &ip, uint16_t port);
    SocketTCPMaster(uint16_t port, bool ipv6);

    // don't share anything, all the fields are static
    SocketTCPMaster(const SocketTCPMaster &other) = delete;
    SocketTCPMaster &operator=(const SocketTCPMaster &) = delete;
    SocketTCPMaster(SocketTCPMaster &&other);
    SocketTCPMaster &operator=(SocketTCPMaster &&other);

    ~SocketTCPMaster() = default;

    SocketTCP accept(UnknownAddress &unkwAddr) const;
};

class SocketTCP : public ASocket {
public:
    enum EventType {
        NONE = 0,
        READ,
        WRITE,
    };

public:
    SocketTCP() = default;
    SocketTCP(const SocketTCPMaster &socketMaster, UnknownAddress &unkwAddr,
              bool block = false);                                          // accepts it from the socket master
    SocketTCP(const AddressV4 &addr, uint16_t tcpPort, bool block = false); // connect to the address (only for client)
    SocketTCP(const AddressV6 &addr, uint16_t tcpPort, bool block = false); // connect to the address (only for client)
    SocketTCP(const SocketTCP &other) = delete;
    SocketTCP &operator=(const SocketTCP &) = delete;
    SocketTCP(SocketTCP &&other);
    SocketTCP &operator=(SocketTCP &&other);
    ~SocketTCP() = default;

    bool send(const TCPMessage &msg) const;
    void receive(TCPMessage &msg) const;

    const EventType getEventType(void) const {
        return m_eventType;
    }
    const bool isNotReady(void) const {
        return m_notReady;
    }

private:
    std::size_t receiveReliant(TCPSerializedMessage *buffer, std::size_t size) const;
    std::size_t sendReliant(const TCPSerializedMessage *msg, std::size_t msgDataSize) const;

    EventType m_eventType = READ;
    bool m_notReady = true;
};

SocketTCPMaster openSocketTcp(const IP &ip, uint16_t wantedPort);
SocketUDP openSocketUdp(const IP &ip, uint16_t wantedPort);
SocketTCPMaster openSocketTcp(uint16_t wantedPort, bool ipv6);
SocketUDP openSocketUdp(uint16_t wantedPort, bool ipv6);

} // namespace Network
