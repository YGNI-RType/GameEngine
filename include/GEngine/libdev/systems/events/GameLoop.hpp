/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** GameLoop.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"

namespace gengine::system::event {
struct GameLoop : public Event {
    float deltaTime;
    GameLoop(float &deltaTime)
        : deltaTime(deltaTime) {
    }
    GameLoop(float &&deltaTime)
        : deltaTime(deltaTime) {
    }
};

} // namespace gengine::system::event
