/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Event
** ════════════════════════════════════════════════════════════════════════════
**  File        : Mouse.hpp
**  Create at   : 2024-10-15 05:13
**  Author      : AUTHOR
**  Description : These events transmit information related to the mouse,
                    they are emitted by the MouseCatcher system dedicated to
                    the DriverEngine.
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "module/raylib_safe.h"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/driver/input/State.hpp"

namespace gengine::system::event::driver::input {
class MouseButton : public Event {
public:
    MouseButton(state_t state, const Vector2 &cursorPos)
        : state(state)
        , cursorPos(cursorPos) {
    }
    MouseButton(state_t state, const Vector2 &&cursorPos)
        : state(state)
        , cursorPos(cursorPos) {
    }
    state_t state;
    Vector2 cursorPos;
};

class Mouse_Left : public MouseButton {
public:
    Mouse_Left(state_t state, const Vector2 &cursorPos)
        : MouseButton(state, cursorPos) {
    }
    Mouse_Left(state_t state, const Vector2 &&cursorPos)
        : MouseButton(state, cursorPos) {
    }
};
class Mouse_Right : public MouseButton {
public:
    Mouse_Right(state_t state, const Vector2 &cursorPos)
        : MouseButton(state, cursorPos) {
    }
    Mouse_Right(state_t state, const Vector2 &&cursorPos)
        : MouseButton(state, cursorPos) {
    }
};
class Mouse_Middle : public MouseButton {
public:
    Mouse_Middle(state_t state, const Vector2 &cursorPos)
        : MouseButton(state, cursorPos) {
    }
    Mouse_Middle(state_t state, const Vector2 &&cursorPos)
        : MouseButton(state, cursorPos) {
    }
};
} // namespace gengine::system::event::driver::input
