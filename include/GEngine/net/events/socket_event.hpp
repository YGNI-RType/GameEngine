/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** socket_event
*/

#pragma once

#include "../net_socket.hpp"

namespace Network::Event {
#ifdef _WIN32
#include <atomic>
#include <winsock2.h>
#include <ws2tcpip.h>

#undef interface

#else
#include <sys/eventfd.h>
#include <unistd.h>
#endif

class SocketEvent : public ASocket {
public:
    SocketEvent();
    ~SocketEvent();

    SocketEvent(const SocketEvent &other) = delete;
    SocketEvent &operator=(const SocketEvent &other) = delete;
    SocketEvent(SocketEvent &&other);
    SocketEvent &operator=(SocketEvent &&other);

    void signal();
    void wait();

#ifdef _WIN32
private:
    SOCKET m_sockConnect = -1;
    std::atomic_bool m_hasRead = false;
#endif
};
} // namespace Network::Event
