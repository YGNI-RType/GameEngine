/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** RenderLoop.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"

namespace gengine::system::event {
struct RenderLoop : public Event {
    float deltaTime;
    RenderLoop(float &deltaTime)
        : deltaTime(deltaTime) {
    }
    RenderLoop(float &&deltaTime)
        : deltaTime(deltaTime) {
    }
};

struct StopRenderLoop : public Event {};
} // namespace gengine::system::event
