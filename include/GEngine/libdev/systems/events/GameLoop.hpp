/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Event
** ════════════════════════════════════════════════════════════════════════════
**  File        : GameLoop.hpp
**  Create at   : 2024-10-15 05:17
**  Author      : AUTHOR
**  Description : This event dedicated to the GameEngine is natively published
                    by the AutoMainLoop system and allows you to pace the
                    game logic.
                    !! ATTENTION do not publish it !!
** ════════════════════════════════════════════════════════════════════════════
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
