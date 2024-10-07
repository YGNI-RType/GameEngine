/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Log.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include <typeindex>

namespace gengine::system::event {
struct Log : public Event {
    std::string message;
    Log(const std::string &message)
        : message(message) {
    }
    Log(const std::string &&message)
        : message(message) {
    }
};
} // namespace gengine::system::event
