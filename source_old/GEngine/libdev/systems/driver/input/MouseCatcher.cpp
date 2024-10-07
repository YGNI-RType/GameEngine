/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MouseCatcher.cpp
*/

#include "GEngine/libdev/systems/driver/input/MouseCatcher.hpp"
#include <iostream>

namespace gengine::system::driver::input {
void MouseCatcher::init(void) { subscribeToEvent<gengine::system::event::MainLoop>(&MouseCatcher::onMainLoop); }

void MouseCatcher::onMainLoop(gengine::system::event::MainLoop &e) {
    MouseButton button = MOUSE_BUTTON_LEFT;
    do {
        if (IsMouseButtonReleased(button))
            processMouseInput(button, InputState::RELEASE);
        if (IsMouseButtonPressed(button))
            processMouseInput(button, InputState::PRESSED);
        if (IsMouseButtonDown(button))
            processMouseInput(button, InputState::DOWN);
        ++button;
    } while (button != MOUSE_BUTTON_LEFT);
}

void MouseCatcher::processMouseInput(int button, InputState state) {
    Vector2 cursorPos = GetMousePosition();
    switch (button) {
    case MOUSE_BUTTON_LEFT:
        publishEvent(MouseLeftEvent(state, cursorPos));
        break;
    case MOUSE_BUTTON_RIGHT:
        publishEvent(MouseRightEvent(state, cursorPos));
        break;
    case MOUSE_BUTTON_MIDDLE:
        publishEvent(MouseMiddleEvent(state, cursorPos));
        break;
    default:
        break;
    }
}
} // namespace gengine::system::driver::input
