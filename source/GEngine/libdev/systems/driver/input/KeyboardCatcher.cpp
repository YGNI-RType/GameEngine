/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** KeyboardCatcher.cpp
*/

#include "GEngine/libdev/systems/driver/input/KeyboardCatcher.hpp"
#include <iostream>

namespace gengine::system::driver::input {
void KeyboardCatcher::init(void) {
    subscribeToEvent<gengine::system::event::RenderLoop>(&KeyboardCatcher::onMainLoop);
}

void KeyboardCatcher::onMainLoop(gengine::system::event::RenderLoop &e) {
    for (KeyboardKey key = KEY_SPACE; key != KEY_NULL; ++key) {
        if (IsKeyReleased(key))
            processKeyInput(key, InputState::RELEASE);
        if (IsKeyPressed(key))
            processKeyInput(key, InputState::PRESSED);
        if (IsKeyDown(key))
            processKeyInput(key, InputState::DOWN);
    }
    PollInputEvents();
}

void KeyboardCatcher::processKeyInput(int key, InputState state) {
    switch (key) {
    case KEY_APOSTROPHE:
        publishEvent(KeyApostropheEvent(state));
        break;
    case KEY_COMMA:
        publishEvent(KeyCommaEvent(state));
        break;
    case KEY_MINUS:
        publishEvent(KeyMinusEvent(state));
        break;
    case KEY_PERIOD:
        publishEvent(KeyPeriodEvent(state));
        break;
    case KEY_SLASH:
        publishEvent(KeySlashEvent(state));
        break;
    case KEY_ZERO:
        publishEvent(KeyZeroEvent(state));
        break;
    case KEY_ONE:
        publishEvent(KeyOneEvent(state));
        break;
    case KEY_TWO:
        publishEvent(KeyTwoEvent(state));
        break;
    case KEY_THREE:
        publishEvent(KeyThreeEvent(state));
        break;
    case KEY_FOUR:
        publishEvent(KeyFourEvent(state));
        break;
    case KEY_FIVE:
        publishEvent(KeyFiveEvent(state));
        break;
    case KEY_SIX:
        publishEvent(KeySixEvent(state));
        break;
    case KEY_SEVEN:
        publishEvent(KeySevenEvent(state));
        break;
    case KEY_EIGHT:
        publishEvent(KeyEightEvent(state));
        break;
    case KEY_NINE:
        publishEvent(KeyNineEvent(state));
        break;
    case KEY_SEMICOLON:
        publishEvent(KeySemicolonEvent(state));
        break;
    case KEY_EQUAL:
        publishEvent(KeyEqualEvent(state));
        break;
    case KEY_A:
        publishEvent(KeyAEvent(state));
        break;
    case KEY_B:
        publishEvent(KeyBEvent(state));
        break;
    case KEY_C:
        publishEvent(KeyCEvent(state));
        break;
    case KEY_D:
        publishEvent(KeyDEvent(state));
        break;
    case KEY_E:
        publishEvent(KeyEEvent(state));
        break;
    case KEY_F:
        publishEvent(KeyFEvent(state));
        break;
    case KEY_G:
        publishEvent(KeyGEvent(state));
        break;
    case KEY_H:
        publishEvent(KeyHEvent(state));
        break;
    case KEY_I:
        publishEvent(KeyIEvent(state));
        break;
    case KEY_J:
        publishEvent(KeyJEvent(state));
        break;
    case KEY_K:
        publishEvent(KeyKEvent(state));
        break;
    case KEY_L:
        publishEvent(KeyLEvent(state));
        break;
    case KEY_M:
        publishEvent(KeyMEvent(state));
        break;
    case KEY_N:
        publishEvent(KeyNEvent(state));
        break;
    case KEY_O:
        publishEvent(KeyOEvent(state));
        break;
    case KEY_P:
        publishEvent(KeyPEvent(state));
        break;
    case KEY_Q:
        publishEvent(KeyQEvent(state));
        break;
    case KEY_R:
        publishEvent(KeyREvent(state));
        break;
    case KEY_S:
        publishEvent(KeySEvent(state));
        break;
    case KEY_T:
        publishEvent(KeyTEvent(state));
        break;
    case KEY_U:
        publishEvent(KeyUEvent(state));
        break;
    case KEY_V:
        publishEvent(KeyVEvent(state));
        break;
    case KEY_W:
        publishEvent(KeyWEvent(state));
        break;
    case KEY_X:
        publishEvent(KeyXEvent(state));
        break;
    case KEY_Y:
        publishEvent(KeyYEvent(state));
        break;
    case KEY_Z:
        publishEvent(KeyZEvent(state));
        break;
    case KEY_LEFT_BRACKET:
        publishEvent(KeyLeftBracketEvent(state));
        break;
    case KEY_BACKSLASH:
        publishEvent(KeyBackslashEvent(state));
        break;
    case KEY_RIGHT_BRACKET:
        publishEvent(KeyRightBracketEvent(state));
        break;
    case KEY_GRAVE:
        publishEvent(KeyGraveEvent(state));
        break;
    case KEY_SPACE:
        publishEvent(KeySpaceEvent(state));
        break;
    case KEY_ESCAPE:
        publishEvent(KeyEscapeEvent(state));
        break;
    case KEY_ENTER:
        publishEvent(KeyEnterEvent(state));
        break;
    case KEY_TAB:
        publishEvent(KeyTabEvent(state));
        break;
    case KEY_BACKSPACE:
        publishEvent(KeyBackspaceEvent(state));
        break;
    case KEY_INSERT:
        publishEvent(KeyInsertEvent(state));
        break;
    case KEY_DELETE:
        publishEvent(KeyDeleteEvent(state));
        break;
    case KEY_RIGHT:
        publishEvent(KeyRightEvent(state));
        break;
    case KEY_LEFT:
        publishEvent(KeyLeftEvent(state));
        break;
    case KEY_DOWN:
        publishEvent(KeyDownEvent(state));
        break;
    case KEY_UP:
        publishEvent(KeyUpEvent(state));
        break;
    case KEY_PAGE_UP:
        publishEvent(KeyPageUpEvent(state));
        break;
    case KEY_PAGE_DOWN:
        publishEvent(KeyPageDownEvent(state));
        break;
    case KEY_HOME:
        publishEvent(KeyHomeEvent(state));
        break;
    case KEY_END:
        publishEvent(KeyEndEvent(state));
        break;
    case KEY_CAPS_LOCK:
        publishEvent(KeyCapsLockEvent(state));
        break;
    case KEY_SCROLL_LOCK:
        publishEvent(KeyScrollLockEvent(state));
        break;
    case KEY_NUM_LOCK:
        publishEvent(KeyNumLockEvent(state));
        break;
    case KEY_PRINT_SCREEN:
        publishEvent(KeyPrintScreenEvent(state));
        break;
    case KEY_PAUSE:
        publishEvent(KeyPauseEvent(state));
        break;
    case KEY_F1:
        publishEvent(KeyF1Event(state));
        break;
    case KEY_F2:
        publishEvent(KeyF2Event(state));
        break;
    case KEY_F3:
        publishEvent(KeyF3Event(state));
        break;
    case KEY_F4:
        publishEvent(KeyF4Event(state));
        break;
    case KEY_F5:
        publishEvent(KeyF5Event(state));
        break;
    case KEY_F6:
        publishEvent(KeyF6Event(state));
        break;
    case KEY_F7:
        publishEvent(KeyF7Event(state));
        break;
    case KEY_F8:
        publishEvent(KeyF8Event(state));
        break;
    case KEY_F9:
        publishEvent(KeyF9Event(state));
        break;
    case KEY_F10:
        publishEvent(KeyF10Event(state));
        break;
    case KEY_F11:
        publishEvent(KeyF11Event(state));
        break;
    case KEY_F12:
        publishEvent(KeyF12Event(state));
        break;
    case KEY_LEFT_SHIFT:
        publishEvent(KeyLeftShiftEvent(state));
        break;
    case KEY_LEFT_CONTROL:
        publishEvent(KeyLeftControlEvent(state));
        break;
    case KEY_LEFT_ALT:
        publishEvent(KeyLeftAltEvent(state));
        break;
    case KEY_LEFT_SUPER:
        publishEvent(KeyLeftSuperEvent(state));
        break;
    case KEY_RIGHT_SHIFT:
        publishEvent(KeyRightShiftEvent(state));
        break;
    case KEY_RIGHT_CONTROL:
        publishEvent(KeyRightControlEvent(state));
        break;
    case KEY_RIGHT_ALT:
        publishEvent(KeyRightAltEvent(state));
        break;
    case KEY_RIGHT_SUPER:
        publishEvent(KeyRightSuperEvent(state));
        break;
    case KEY_KB_MENU:
        publishEvent(KeyKBMenuEvent(state));
        break;
    case KEY_KP_0:
        publishEvent(KeyKP0Event(state));
        break;
    case KEY_KP_1:
        publishEvent(KeyKP1Event(state));
        break;
    case KEY_KP_2:
        publishEvent(KeyKP2Event(state));
        break;
    case KEY_KP_3:
        publishEvent(KeyKP3Event(state));
        break;
    case KEY_KP_4:
        publishEvent(KeyKP4Event(state));
        break;
    case KEY_KP_5:
        publishEvent(KeyKP5Event(state));
        break;
    case KEY_KP_6:
        publishEvent(KeyKP6Event(state));
        break;
    case KEY_KP_7:
        publishEvent(KeyKP7Event(state));
        break;
    case KEY_KP_8:
        publishEvent(KeyKP8Event(state));
        break;
    case KEY_KP_9:
        publishEvent(KeyKP9Event(state));
        break;
    case KEY_KP_DECIMAL:
        publishEvent(KeyKPDecimalEvent(state));
        break;
    case KEY_KP_DIVIDE:
        publishEvent(KeyKPDivideEvent(state));
        break;
    case KEY_KP_MULTIPLY:
        publishEvent(KeyKPMultiplyEvent(state));
        break;
    case KEY_KP_SUBTRACT:
        publishEvent(KeyKPSubtractEvent(state));
        break;
    case KEY_KP_ADD:
        publishEvent(KeyKPAddEvent(state));
        break;
    case KEY_KP_ENTER:
        publishEvent(KeyKPEnterEvent(state));
        break;
    case KEY_KP_EQUAL:
        publishEvent(KeyKPEqualEvent(state));
        break;
    default:
        break;
    }
}

KeyboardKey &operator++(KeyboardKey &key) {
    if (key <= 348)
        key = static_cast<KeyboardKey>(static_cast<int>(key) + 1);
    else
        key = KEY_NULL;
    return key;
}
} // namespace gengine::system::driver::input
