/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event_socket
*/

#include "GEngine/net/events/socket_event.hpp"

#ifdef HAS_NOT_EVENTFD
#include <stdexcept>
#include <unistd.h>
#endif

namespace Network::Event {

SocketEvent::SocketEvent() {
#ifdef HAS_NOT_EVENTFD
    int pipefd[2];
    if (pipe(pipefd) == -1)
        throw std::runtime_error("Failed to create pipe");

    int flags = fcntl(pipefd[1], F_GETFL, 0);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);
    int pipe_sz = fcntl(pipefd[1], F_SETPIPE_SZ, 1);

    m_sock = pipefd[0];
    m_sockConnect = pipefd[1];
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
        close(m_sockConnect);
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
    size_t sze = write(m_sockConnect, buf, sizeof(buf));
#else
    eventfd_write(m_sock, 1);
#endif
}

void SocketEvent::wait() {
#ifdef HAS_NOT_EVENTFD
    char buf[1];
    read(m_sock, buf, sizeof(buf));
#else
    eventfd_t c;
    eventfd_read(m_sock, &c);
#endif
}
} // namespace Network::Event
