/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event_io
*/

#include "GEngine/net/net_event_io.hpp"

#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <stdexcept>
#include <unistd.h>

namespace Network::Event {

IO::IO() {
    if (pipe(m_pipe) < 0)
        throw std::runtime_error("Failed to create pipe");
        // throw std::runtime_error("Failed to create pipe: %s (%d)", strerror(errno), errno);

    if (fcntl(m_pipe[0], F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("Failed to set pipe non-blocking mode");
        // throw std::runtime_error("Failed to set pipe non-blocking mode: %s (%d)", strerror(errno), errno);
}

IO::IO(const IO &other) {
    m_pipe[0] = other.m_pipe[0];
    m_pipe[1] = other.m_pipe[1];
}

IO::~IO() {
    if (m_pipe[0] >= 0) {
        close(m_pipe[0]);
        m_pipe[0] = -1;
    }

    if (m_pipe[1] >= 0) {
        close(m_pipe[1]);
        m_pipe[1] = -1;
    }
}

void IO::writeUpdate() {
    write(m_pipe[1], "", 1);
}

void IO::readUpdate() {
    uint8_t buf;

    while (read(m_pipe[0], &buf, 1) == 1)
        ;
}

} // namespace Network::Event