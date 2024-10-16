/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : MouseCatcher.hpp
**  Create at   : 2024-10-15 04:59
**  Author      : AUTHOR
**  Description : This system is dedicated to the DriverEngine, it must with
                    the raylib publish all the events linked mouse.
** ═══════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "module/raylib_safe.h"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/libdev/systems/events/driver/input/Mouse.hpp"

namespace gengine::system::driver::input {
using InputState = gengine::system::event::driver::input::state_t;
class MouseCatcher : public gengine::System<MouseCatcher> {
public:
    void init(void) override;

    void onMainLoop(gengine::system::event::MainLoop &e);

private:
    void processMouseInput(int key, InputState state);
};

MouseButton &operator++(MouseButton &key) {
    key = key < MOUSE_BUTTON_MIDDLE ? static_cast<MouseButton>(static_cast<int>(key) + 1) : MOUSE_BUTTON_LEFT;
    return key;
}

using MouseLeftEvent = gengine::system::event::driver::input::Mouse_Left;
using MouseRightEvent = gengine::system::event::driver::input::Mouse_Right;
using MouseMiddleEvent = gengine::system::event::driver::input::Mouse_Middle;
} // namespace gengine::system::driver::input