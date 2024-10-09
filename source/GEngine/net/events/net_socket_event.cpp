/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event_socket
*/

#include "GEngine/net/events/socket_event.hpp"

namespace Network::Event {

SocketEvent::SocketEvent() {
#ifdef _WIN32
    m_sockConnect = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockConnect == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    }

    auto listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    }

    unsigned int opt = 1;
    setsockopt(listenSock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char *)&opt, (socklen_t)sizeof(opt));

    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = 0;

    if (bind(listenSock, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(listenSock);
        WSACleanup();
        throw std::runtime_error("Failed to bind socket");
    }

    int len = sizeof(addr);
    if (getsockname(listenSock, (struct sockaddr *)&addr, &len) == SOCKET_ERROR) {
        closesocket(listenSock);
        WSACleanup();
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(listenSock, 1) == -1) {
        closesocket(listenSock);
        WSACleanup();
        throw std::runtime_error("Failed to bind socket");
    }

    if (connect(m_sockConnect, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cout << WSAGetLastError() << std::endl;
        closesocket(m_sockConnect);
        WSACleanup();
        throw std::runtime_error("Failed to connect to socket");
    }

    /** warning : todo https://github.com/python/cpython/pull/122134/files
     * avec cette méthode, on peut se faire hijack cette connexion. même si osef ça peut faire chier
     */

    m_sock = accept(listenSock, nullptr, nullptr);
    if (m_sock == SOCKET_ERROR) {
        closesocket(m_sock);
        WSACleanup();
        throw std::runtime_error("Failed to connect to socket");
    }

    closesocket(listenSock);
#else
    m_sock = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (m_sock == -1)
        throw std::runtime_error("Failed to create eventfd");
#endif
}

SocketEvent::~SocketEvent() {
#ifdef _WIN32
    if (m_sockConnect != -1)
        closesocket(m_sockConnect);
#endif
}

SocketEvent::SocketEvent(SocketEvent &&other) : ASocket(std::move(other))
{
    m_sock = other.m_sock;
#ifdef _WIN32
    m_sockConnect = other.m_sockConnect;
    other.m_sockConnect = -1;
#endif
    other.m_sock = -1;
}

SocketEvent &SocketEvent::operator=(SocketEvent &&other)
{
    if (this != &other) {
        m_sock = other.m_sock;
        other.m_sock = -1;
    }
    return *this;
}

void SocketEvent::signal() {
#ifdef _WIN32
    char buf[1] = {0};
    send(m_sockConnect, buf, sizeof(buf), 0);
#else
    eventfd_write(m_sock, 1);
#endif
}

void SocketEvent::wait() {
#ifdef _WIN32
    char buf[1];
    recv(m_sock, buf, sizeof(buf), 0);
#else
    eventfd_t c;
    eventfd_read(m_sock, &c);
#endif
}
} // namespace Network::Event
