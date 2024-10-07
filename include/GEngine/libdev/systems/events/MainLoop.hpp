/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MainLoop.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"

namespace gengine::system::event {
struct MainLoop : public Event {
    float deltaTime;
    MainLoop(float &deltaTime)
        : deltaTime(deltaTime) {
    }
    MainLoop(float &&deltaTime)
        : deltaTime(deltaTime) {
    }
};

struct StopMainLoop : public Event {};
} // namespace gengine::system::event
