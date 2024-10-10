/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** socketError
*/

#pragma once

#include <exception>

namespace Network {

class SocketException : public std::exception {
public:
    SocketException(const char *msg, bool shouldRetry = true)
        : m_msg(msg)
        , m_shouldRetry(shouldRetry) {
    }

    const char *what() const noexcept override {
        return m_msg;
    }

    bool shouldRetry() const {
        return m_shouldRetry;
    }

private:
    const char *m_msg;
    bool m_shouldRetry;
};

class SocketDisconnected : public SocketException {
public:
    SocketDisconnected()
        : SocketException("Incomming Socket disconnected") {
    }
};
} // namespace Network
