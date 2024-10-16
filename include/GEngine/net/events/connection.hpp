/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** connection
*/

#pragma once

#include <cstdint>
#include <string>

namespace Network::Event {
struct ConnectInfo {
    std::string ip;
    uint16_t port;

    ConnectInfo(const std::string &ip, uint16_t port)
        : ip(ip)
        , port(port) {};
    size_t pingIndex = -1;
};

} // namespace Network::Event
