/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Event
** ════════════════════════════════════════════════════════════════════════════
**  File        : RenderLoop.hpp
**  Create at   : 2024-10-15 05:17
**  Author      : AUTHOR
**  Description : This event dedicated to the DriverEngine is natively published
                    by the AutoMainLoop system and allows you to pace the
                    driver logic.
                    !! ATTENTION do not publish it !!
** ════════════════════════════════════════════════════════════════════════════
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
