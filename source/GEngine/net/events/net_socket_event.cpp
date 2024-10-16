/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event_socket
*/

#include "GEngine/net/events/socket_event.hpp"

#include <stdexcept>

#ifdef HAS_NOT_EVENTFD
#if defined(__APPLE__) || defined(__unix__)
#define closesocket close
#include <unistd.h>
#else
#include <cstring>
#endif
#endif

namespace Network::Event {

SocketEvent::SocketEvent() {
#ifdef HAS_NOT_EVENTFD
#if defined(__APPLE__) || defined(__unix__)
    int pipefd[2];
    if (pipe(pipefd) == -1)
        throw std::runtime_error("Failed to create pipe");

    int flags = fcntl(pipefd[1], F_GETFL, 0);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);
#if __linux__
    int pipe_sz = fcntl(pipefd[1], F_SETPIPE_SZ, 1);
#endif

    m_sock = pipefd[0];
    m_sockConnect = pipefd[1];
#else
    ASocket::initLibs();
    m_sockConnect = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockConnect == INVALID_SOCKET)
        throw std::runtime_error("Failed to create socket");

    auto listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET)
        throw std::runtime_error("Failed to create socket");

    unsigned int opt = 1;
    setsockopt(listenSock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char *)&opt, (socklen_t)sizeof(opt));

    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = 0;

    if (bind(listenSock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        closesocket(listenSock);
        throw std::runtime_error("Failed to bind socket");
    }

    int len = sizeof(addr);
    if (getsockname(listenSock, (struct sockaddr *)&addr, &len) == -1) {
        closesocket(listenSock);
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(listenSock, 1) == -1) {
        closesocket(listenSock);
        throw std::runtime_error("Failed to bind socket");
    }

    if (connect(m_sockConnect, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        closesocket(m_sockConnect);
        throw std::runtime_error("Failed to connect to socket");
    }

    /** warning : todo https://github.com/python/cpython/pull/122134/files
     * avec cette méthode, on peut se faire hijack cette connexion. même si osef ça peut faire chier
     */

    m_sock = accept(listenSock, nullptr, nullptr);
    if (m_sock == -1) {
        closesocket(m_sock);
        throw std::runtime_error("Failed to connect to socket");
    }

    closesocket(listenSock);
#endif
#else
    m_sock = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (m_sock == -1)
        throw std::runtime_error("Failed to create eventfd");
#endif
    addSocketPool(m_sock);
}

SocketEvent::~SocketEvent() {
#ifdef HAS_NOT_EVENTFD
    if (m_sockConnect != -1)
        closesocket(m_sockConnect);
#endif
}

SocketEvent::SocketEvent(SocketEvent &&other)
    : ASocket(std::move(other)) {
#ifdef HAS_NOT_EVENTFD
    m_sockConnect = other.m_sockConnect;
    other.m_sockConnect = -1;
#endif
}

SocketEvent &SocketEvent::operator=(SocketEvent &&other) {
    if (this != &other) {
        ASocket::operator=(std::move(other));
#ifdef HAS_NOT_EVENTFD
        m_sockConnect = other.m_sockConnect;
        other.m_sockConnect = -1;
#endif
    }
    return *this;
}

void SocketEvent::signal() {
#ifdef HAS_NOT_EVENTFD
    char buf[1] = {0};
#ifdef _WIN32
    if (!m_hasRead)
        return;
    send(m_sockConnect, buf, sizeof(buf), 0);
    m_hasRead = false;
#else
    write(m_sockConnect, buf, sizeof(buf));
#endif
#else
    eventfd_write(m_sock, 1);
#endif
}

void SocketEvent::wait() {
#ifdef HAS_NOT_EVENTFD
    char buf[1];
#ifdef _WIN32
    if (!m_hasRead)
        return;
    recv(m_sockConnect, buf, sizeof(buf), 0);
    m_hasRead = true;
#else
    read(m_sock, buf, sizeof(buf));
#endif
#else
    eventfd_t c;
    eventfd_read(m_sock, &c);
#endif
}
} // namespace Network::Event
