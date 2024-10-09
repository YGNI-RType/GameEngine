/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** connection
*/

#pragma once

#include <cstdint>
#include <string>

namespace Network::Event
{
    struct ConnectInfo {
        size_t pingIndex;

        std::string ip;
        uint16_t port;
    };

    
} // namespace Network
