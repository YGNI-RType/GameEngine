/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Mouse.hpp
*/

/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Keyboard.hpp
*/

#pragma once

#include <raylib.h>

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/driver/input/State.hpp"

namespace gengine::system::event::driver::input {
class MouseButton : public Event {
public:
    MouseButton(state_t state, const Vector2 &cursorPos) : state(state), cursorPos(cursorPos) {}
    MouseButton(state_t state, const Vector2 &&cursorPos) : state(state), cursorPos(cursorPos) {}
    state_t state;
    Vector2 cursorPos;
};

class Mouse_Left : public MouseButton {
public:
    Mouse_Left(state_t state, const Vector2 &cursorPos) : MouseButton(state, cursorPos) {}
    Mouse_Left(state_t state, const Vector2 &&cursorPos) : MouseButton(state, cursorPos) {}
};
class Mouse_Right : public MouseButton {
public:
    Mouse_Right(state_t state, const Vector2 &cursorPos) : MouseButton(state, cursorPos) {}
    Mouse_Right(state_t state, const Vector2 &&cursorPos) : MouseButton(state, cursorPos) {}
};
class Mouse_Middle : public MouseButton {
public:
    Mouse_Middle(state_t state, const Vector2 &cursorPos) : MouseButton(state, cursorPos) {}
    Mouse_Middle(state_t state, const Vector2 &&cursorPos) : MouseButton(state, cursorPos) {}
};
} // namespace gengine::system::event::driver::input
