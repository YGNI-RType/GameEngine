/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** InputsToGameEvents.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/driver/input/KeyboardCatcher.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"

#include "events/Movement.hpp"
#include "events/Shoot.hpp"

namespace rtype::system {
class InputsToGameEvents : public gengine::System<InputsToGameEvents, gengine::system::driver::input::KeyboardCatcher> {
public:
    void init(void) override;
    void sendEvents(gengine::system::event::GameLoop &e);

    void moveUp(gengine::system::driver::input::KeyUpEvent &e);
    void moveLeft(gengine::system::driver::input::KeyLeftEvent &e);
    void moveDown(gengine::system::driver::input::KeyDownEvent &e);
    void moveRight(gengine::system::driver::input::KeyRightEvent &e);

    void shoot(gengine::system::driver::input::KeySpaceEvent &e);

private:
    event::Shoot::State m_shootState;

    char m_directionBitmask = 0;
    static const char UP_MASK = 1 << 0;    // 0b0001
    static const char RIGHT_MASK = 1 << 1; // 0b1000
    static const char DOWN_MASK = 1 << 2;  // 0b0010
    static const char LEFT_MASK = 1 << 3;  // 0b0100
    void updateDirectionBitmask(event::Movement::State state, bool);
    event::Movement::State getMovementState(void);
};
} // namespace rtype::system
