/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Event
** ════════════════════════════════════════════════════════════════════════════
**  File        : MainLoop.hpp
**  Create at   : 2024-10-15 05:20
**  Author      : AUTHOR
**  Description : This event is natively published by the AutoMainLoop system
                    and allows the proper functioning of the entire engine.
                    !! ATTENTION do not publish it !!

                    The StopMainLoop event is used to stop the auto-publishing
                    of MainLoop.
** ════════════════════════════════════════════════════════════════════════════
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
