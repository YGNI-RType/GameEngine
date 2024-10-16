/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** socket_event
*/

#pragma once

#include "../net_socket.hpp"

#ifdef _WIN32
#else
#ifndef __APPLE__
#include <sys/eventfd.h>
#endif
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(__APPLE__)
#define HAS_NOT_EVENTFD = 1
#endif

namespace Network::Event {
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

#ifdef HAS_NOT_EVENTFD
private:
    SOCKET m_sockConnect = -1;
#endif
};
} // namespace Network::Event
