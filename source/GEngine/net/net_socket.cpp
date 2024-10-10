/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** socket
*/

#include "GEngine/net/net_socket.hpp"
#include "GEngine/cvar/net.hpp"
#include "GEngine/net/net_socket_error.hpp"

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>

// temp
#include <iostream>

#ifdef _WIN32
#include <WS2tcpip.h>
#include <winsock2.h>
#include <ws2spi.h>
#include <ws2tcpip.h>

#undef interface

#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace Network {

#ifdef _WIN32
WSADATA ASocket::winsockdata;
#endif

SOCKET ASocket::m_highFd = -1;
fd_set ASocket::m_fdSet;

ASocket::~ASocket() {
    socketClose();
}

ASocket::ASocket(ASocket &&other) {
    m_sock = other.m_sock;
    other.m_sock = -1;
}

ASocket &ASocket::operator=(ASocket &&other) {
    if (this != &other) {
        m_sock = other.m_sock;
        other.m_sock = -1;
    }
    return *this;
}

//////////////////////////////////////

void ASocket::initLibs(void) {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(1, 1), &winsockdata)) {
        // Com_Printf( "WARNING: Winsock initialization failed, returned %d\n",
        // r );
        return;
    }

    // Com_Printf( "Winsock Initialized\n" );
#endif
    FD_ZERO(&m_fdSet);
}

int ASocket::socketClose(void) {
    int status = 0;

    if (m_sock == -1)
        return 0;

#ifdef _WIN32
    status = shutdown(m_sock, SD_BOTH);
    if (status == 0)
        status = closesocket(m_sock);
#else
    status = shutdown(m_sock, SHUT_RDWR);
    if (status == 0)
        status = close(m_sock);
#endif

    if (m_sock == m_highFd)
        while (!FD_ISSET(m_highFd, &m_fdSet))
            (m_highFd)--;

    return status;
}

void ASocket::addSocketPool(SOCKET socket) {
    FD_SET(socket, &m_fdSet);
    if (socket > m_highFd)
        m_highFd = socket;
}

//////////////////////////////////////

ANetSocket::ANetSocket(ANetSocket &&other) {
    m_sock = other.m_sock;
    m_port = other.m_port;
    other.m_sock = -1;
}

ANetSocket &ANetSocket::operator=(ANetSocket &&other) {
    if (this != &other)
        m_port = other.m_port;
    ASocket::operator=(std::move(other));
    return *this;
}

void ANetSocket::setBlocking(bool blocking) {
#ifdef _WIN32
    u_long mode = blocking ? 0 : 1;
    ioctlsocket(m_sock, FIONBIO, &mode);
#else
    int flags = fcntl(m_sock, F_GETFL, 0);
    if (blocking)
        flags &= ~O_NONBLOCK;
    else
        flags |= O_NONBLOCK;
    fcntl(m_sock, F_SETFL, flags);
#endif
}

bool ANetSocket::isBlocking(void) const {
#ifdef _WIN32
    u_long mode;
    ioctlsocket(m_sock, FIONBIO, &mode);
    return mode == 0;
#else
    int flags = fcntl(m_sock, F_GETFL, 0);
    return (flags & O_NONBLOCK) == 0;
#endif
}

void ANetSocket::translateAutomaticAddressing(struct sockaddr_storage &addr_storage, uint16_t port, bool ipv6) {
    if (!ipv6) {
        struct sockaddr_in *addr = reinterpret_cast<struct sockaddr_in *>(&addr_storage);

        addr->sin_addr.s_addr = htonl(INADDR_ANY);
        addr->sin_family = AF_INET;
        addr->sin_port = htons(port);
    } else {
        struct sockaddr_in6 *addr = reinterpret_cast<struct sockaddr_in6 *>(&addr_storage);

        addr->sin6_addr = IN6ADDR_ANY_INIT;
        addr->sin6_family = AF_INET6;
        addr->sin6_port = htons(port);
    }
}

/***********************************************/

SocketTCPMaster::SocketTCPMaster(const IP &ip, uint16_t port) {
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock == -1)
        throw std::runtime_error("(TCP) Failed to create socket");

    unsigned int opt = 1;
    if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&opt), sizeof(opt)) < 0)
        throw SocketException("(TCP) Failed to set socket options");

    m_port = port;
    struct sockaddr_in address;
    std::memcpy(&address, &ip.addr, sizeof(struct sockaddr_in));

    address.sin_port = htons(port);

    if (bind(m_sock, (sockaddr *)&address, ip.type == AT_IPV6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in)) < 0)
        throw SocketException("(TCP) Failed to bind socket");

    if (listen(m_sock, MAX_LISTEN) < 0)
        throw SocketException("(TCP) Failed to listen on socket");

    addSocketPool(m_sock);
}

SocketTCPMaster::SocketTCPMaster(uint16_t port, bool ipv6) {
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock == -1)
        throw std::runtime_error("(TCP) Failed to create socket");

    unsigned int opt = 1;
    if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&opt), sizeof(opt)) < 0)
        throw SocketException("(TCP) Failed to set socket options");

    m_port = port;
    struct sockaddr_storage address = {0};
    translateAutomaticAddressing(address, port, ipv6);

    if (bind(m_sock, (sockaddr *)&address, ipv6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in)) < 0)
        throw SocketException("(TCP) Failed to bind socket");

    if (listen(m_sock, MAX_LISTEN) < 0)
        throw SocketException("(TCP) Failed to listen on socket");

    addSocketPool(m_sock);
}

SocketTCPMaster::SocketTCPMaster(SocketTCPMaster &&other)
    : ANetSocket(std::move(other)) {
}
SocketTCPMaster &SocketTCPMaster::operator=(SocketTCPMaster &&other) {
    if (this != &other)
        ANetSocket::operator=(std::move(other));
    return *this;
}

SocketTCP SocketTCPMaster::accept(UnknownAddress &unkwAddr) const {
    return std::move(SocketTCP(*this, unkwAddr));
}

/***********************************************/

SocketTCP::SocketTCP(const SocketTCPMaster &socketMaster, UnknownAddress &unkwAddr, bool block) {
    m_sock = accept(socketMaster.getSocket(), unkwAddr.getAddr(), &unkwAddr.getLen());
    setBlocking(block);
    if (m_sock < 0)
        throw std::runtime_error("Failed to accept connection");

    unkwAddr.updateType();
    m_port = socketMaster.getPort();
    m_notReady = false;
    addSocketPool(m_sock);
}

SocketTCP::SocketTCP(const AddressV4 &addr, uint16_t tcpPort, bool block) {
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    setBlocking(block);
    if (m_sock == -1)
        throw std::runtime_error("(TCP) Failed to create socket");

    m_port = tcpPort;
    struct sockaddr_in address;

    addr.toSockAddr(reinterpret_cast<struct sockaddr *>(&address));
    std::memcpy(&address, (struct sockaddr *)&address, sizeof(address));

    address.sin_port = htons(m_port);

    if (connect(m_sock, (sockaddr *)&address, sizeof(address)) < 0) {
        if (errno == EINPROGRESS) {
            addSocketPool(m_sock);
            return;
        }
        socketClose();
        throw SocketException(strerror(errno));
    }

    m_notReady = false;
    addSocketPool(m_sock);
}

SocketTCP::SocketTCP(const AddressV6 &addr, uint16_t tcpPort, bool block) {
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    setBlocking(block);
    if (m_sock == -1)
        throw std::runtime_error("(TCP) Failed to create socket");

    m_port = tcpPort;
    struct sockaddr_in6 address;

    addr.toSockAddr(reinterpret_cast<struct sockaddr *>(&address));
    std::memcpy(&address, (struct sockaddr *)&address, sizeof(address));

    address.sin6_port = htons(m_port);

    if (connect(m_sock, (sockaddr *)&address, sizeof(address)) < 0) {
        if (errno == EINPROGRESS) {
            addSocketPool(m_sock);
            return;
        }
        socketClose();
        throw SocketException(strerror(errno));
    }

    m_notReady = false;
    addSocketPool(m_sock);
}

SocketTCP::SocketTCP(SocketTCP &&other)
    : ANetSocket(std::move(other)) {
}
SocketTCP &SocketTCP::operator=(SocketTCP &&other) {
    if (this != &other)
        ANetSocket::operator=(std::move(other));
    return *this;
}

bool SocketTCP::send(const TCPMessage &msg) const {
    /* TODO : here, we guess the size is enough to
    send, should we break it here or before ? */

    TCPSerializedMessage sMsg;
    msg.getSerialize(sMsg);

    return sendReliant(&sMsg, msg.getSize()) != 0; // if it did not block
}

void SocketTCP::receive(TCPMessage &msg) const {
    TCPSerializedMessage sMsg;
    auto ptrMsg = reinterpret_cast<char *>(&sMsg);

    size_t recvSz = receiveReliant(reinterpret_cast<TCPSerializedMessage *>(ptrMsg), sizeof(HeaderSerializedMessage));
    /* WIN : need to use these parenthesis, to skip windows.h macro (todo : find why +1, another problem with packed
     * structs ?)*/
    recvSz = receiveReliant(reinterpret_cast<TCPSerializedMessage *>(ptrMsg + recvSz),
                            CF_MIN(sMsg.curSize + 1, sizeof(TCPSerializedMessage) - recvSz));

    msg.setSerialize(sMsg);
}

size_t SocketTCP::receiveReliant(TCPSerializedMessage *buffer, size_t size) const {
    size_t receivedTotal = 0;

    while (receivedTotal < size) {
        auto received = ::recv(m_sock, reinterpret_cast<char *>(buffer + receivedTotal), size - receivedTotal, 0);
        if (received < 0)
            throw SocketException(strerror(errno));
        if (received == 0)
            throw SocketDisconnected();
        receivedTotal += received;
    }
    return receivedTotal;
}

/* THIS IS THE ALL MESSAGE, NOT THE JUST DATA */
size_t SocketTCP::sendReliant(const TCPSerializedMessage *msg, size_t msgDataSize) const {
    size_t sentTotal = 0;
    msgDataSize += sizeof(TCPSerializedMessage) - MAX_TCP_MSGLEN;

    while (sentTotal < msgDataSize) {
        auto sent = ::send(m_sock, reinterpret_cast<const char *>(msg + sentTotal), msgDataSize - sentTotal, 0);
        if (sent < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
                return sentTotal;
            throw SocketException("Failed to send message");
        }
        if (sent == 0)
            throw SocketDisconnected();
        sentTotal += sent;
    }
    return sentTotal;
}

/***********************************************/

void SocketUDP::init(bool block, uint16_t port) {
    m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_sock == -1)
        throw std::runtime_error("(UDP) Failed to create socket");

    m_port = port;
    setBlocking(block);

    unsigned int opt = 1;
    if (setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt)))
        throw std::runtime_error("(UDP) Failed to set socket options (SO_BROADCAST)");
#ifdef NET_DONT_FRAG
#ifdef __FreeBSD__ || defined(__APPLE__)
    if (setsockopt(m_sock, IPPROTO_IP, IP_DONTFRAG, &opt, sizeof(opt)))
#else
    if (setsockopt(m_sock, IPPROTO_IP, IP_MTU_DISCOVER, &opt, sizeof(opt)))
#endif
        throw std::runtime_error("(UDP) Failed to set socket options (IP_DONTFRAG)");
#endif
}

SocketUDP::SocketUDP(const IP &ip, uint16_t port, bool block) {
    init(block, port);

    struct sockaddr_in address;
    std::memcpy(&address, &ip.addr, sizeof(address));

    address.sin_port = htons(port);

    if (bind(m_sock, (sockaddr *)&address, ip.type == AT_IPV6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in)) < 0)
        throw SocketException("(UDP) Failed to bind socket");

    addSocketPool(m_sock);
}

SocketUDP::SocketUDP(uint16_t port, bool ipv6, bool block) {
    init(block, port);

    struct sockaddr_storage address = {0};
    translateAutomaticAddressing(address, port, ipv6);

    if (bind(m_sock, (sockaddr *)&address, ipv6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in)) < 0)
        throw SocketException(strerror(errno));

    addSocketPool(m_sock);
}

SocketUDP::SocketUDP(SocketUDP &&other)
    : ANetSocket(std::move(other)) {
}
SocketUDP &SocketUDP::operator=(SocketUDP &&other) {
    if (this != &other)
        ANetSocket::operator=(std::move(other));
    return *this;
}

size_t SocketUDP::send(const UDPMessage &msg, const Address &addr) const {
    /*
        BY THE WAY, m_sock is the same for EVERY CLASS, i don't put it on static
        because it's inherited
    */

    int simval = CVar::net_send_dropsim.getIntValue();
    if (simval > 0) {
        if (rand() < (int)(((double)RAND_MAX) / 100.0 * (double)simval))
            return 0; // drop this packet
    }

    UDPSerializedMessage sMsg;
    size_t size = msg.getSize();
    struct sockaddr_storage sockaddr = {0};
    msg.getSerialize(sMsg);

    addr.toSockAddr(reinterpret_cast<struct sockaddr *>(&sockaddr));
    auto sent =
        sendto(m_sock, reinterpret_cast<const char *>(&sMsg), size + sizeof(UDPSerializedMessage) - MAX_UDP_MSGLEN, 0,
               (struct sockaddr *)&sockaddr, sizeof(struct sockaddr));
    if (sent < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return 0;
        throw SocketException("Failed to send message (invalid address)");
    }
    return sent;
}

bool SocketUDP::receive(struct sockaddr *addr, UDPSerializedMessage &data, socklen_t *len) const {
    size_t recv = recvfrom(m_sock, reinterpret_cast<char *>(&data), sizeof(UDPSerializedMessage), 0, addr, len);
    int64_t recvStatus = recv;

    int simval = CVar::net_recv_dropsim.getIntValue();
    if (simval > 0) {
        if (rand() < (int)(((double)RAND_MAX) / 100.0 * (double)simval))
            return false; // drop this packet
    }

    // checking wouldblock etc... select told us to read so it's not possible
    if (recvStatus < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return false;
        throw SocketException("Failed to receive message");
    }

    if (recv < sizeof(UDPSerializedMessage) - MAX_UDP_MSGLEN)
        return false;
    return true;
}

bool SocketUDP::receiveV4(UDPMessage &msg, AddressV4 &ip) const {
    UDPSerializedMessage sMsg;
    struct sockaddr_in addr = {0};
    socklen_t len = sizeof(addr);

    if (!receive(reinterpret_cast<struct sockaddr *>(&addr), sMsg, &len))
        return false;
    msg.setSerialize(sMsg);

    ip = AddressV4(AT_IPV4, ntohs(addr.sin_port), ntohl(addr.sin_addr.s_addr));
    return true;
}

/* TODO : one day i might directly pack the udpmessage at this point */
bool SocketUDP::receiveV6(UDPMessage &msg, AddressV6 &ip) const {
    UDPSerializedMessage sMsg;
    struct sockaddr_in6 addr;
    socklen_t len = sizeof(addr);

    if (!receive(reinterpret_cast<struct sockaddr *>(&addr), sMsg, &len))
        return false;
    msg.setSerialize(sMsg);

    ip = AddressV6(AT_IPV6, ntohs(addr.sin6_port), addr.sin6_addr, addr.sin6_scope_id);
    return true;
}

/*****************************************************/

SocketTCPMaster openSocketTcp(const IP &ip, uint16_t wantedPort) {
    for (uint16_t i = 0; i < MAX_TRY_PORTS; i++) {
        try {
            return std::move(SocketTCPMaster(ip, wantedPort + i));
        } catch (SocketException &e) {
            if (!e.shouldRetry() || i == MAX_TRY_PORTS - 1)
                throw e;
            continue;
        }
    }
    throw SocketException("Failed to open TCP socket");
}

SocketUDP openSocketUdp(const IP &ip, uint16_t wantedPort) {
    for (uint16_t i = 0; i < MAX_TRY_PORTS; i++) {
        try {
            return std::move(SocketUDP(ip, wantedPort + i));
        } catch (SocketException &e) {
            if (!e.shouldRetry() || i == MAX_TRY_PORTS - 1)
                throw e;
            continue;
        }
    }
    throw SocketException("Failed to open UDP socket");
}

SocketTCPMaster openSocketTcp(uint16_t wantedPort, bool ipv6) {
    for (uint16_t i = 0; i < MAX_TRY_PORTS; i++) {
        try {
            return std::move(SocketTCPMaster(wantedPort + i, ipv6));
        } catch (SocketException &e) {
            if (!e.shouldRetry() || i == MAX_TRY_PORTS - 1)
                throw e;
            continue;
        }
    }
    throw SocketException("Failed to open TCP socket");
}

SocketUDP openSocketUdp(uint16_t wantedPort, bool ipv6) {
    for (uint16_t i = 0; i < MAX_TRY_PORTS; i++) {
        try {
            return std::move(SocketUDP(wantedPort + i, ipv6));
        } catch (SocketException &e) {
            if (!e.shouldRetry() || i == MAX_TRY_PORTS - 1)
                throw e;
            continue;
        }
    }
    throw SocketException("Failed to open UDP socket");
}

} // namespace Network