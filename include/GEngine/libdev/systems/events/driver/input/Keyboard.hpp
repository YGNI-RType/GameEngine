/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Event
** ════════════════════════════════════════════════════════════════════════════
**  File        : Keyboard.hpp
**  Create at   : 2024-10-15 05:11
**  Author      : AUTHOR
**  Description : These events transmit information related to the keyboard,
                    they are emitted by the KeyboardCatcher system dedicated to
                    the DriverEngine.
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/driver/input/State.hpp"

namespace gengine::system::event::driver::input {
class KeyboardKey : public Event {
public:
    KeyboardKey(state_t state)
        : state(state) {
    }
    state_t state;
};

class Key_Apostrophe : public KeyboardKey {
public:
    Key_Apostrophe(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: '
class Key_Comma : public KeyboardKey {
public:
    Key_Comma(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: ,
class Key_Minus : public KeyboardKey {
public:
    Key_Minus(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: -
class Key_Period : public KeyboardKey {
public:
    Key_Period(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: .
class Key_Slash : public KeyboardKey {
public:
    Key_Slash(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: /
class Key_Zero : public KeyboardKey {
public:
    Key_Zero(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 0
class Key_One : public KeyboardKey {
public:
    Key_One(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 1
class Key_Two : public KeyboardKey {
public:
    Key_Two(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 2
class Key_Three : public KeyboardKey {
public:
    Key_Three(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 3
class Key_Four : public KeyboardKey {
public:
    Key_Four(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 4
class Key_Five : public KeyboardKey {
public:
    Key_Five(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 5
class Key_Six : public KeyboardKey {
public:
    Key_Six(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 6
class Key_Seven : public KeyboardKey {
public:
    Key_Seven(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 7
class Key_Eight : public KeyboardKey {
public:
    Key_Eight(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 8
class Key_Nine : public KeyboardKey {
public:
    Key_Nine(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: 9
class Key_Semicolon : public KeyboardKey {
public:
    Key_Semicolon(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: ;
class Key_Equal : public KeyboardKey {
public:
    Key_Equal(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: =

class Key_A : public KeyboardKey {
public:
    Key_A(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: A
class Key_B : public KeyboardKey {
public:
    Key_B(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: B
class Key_C : public KeyboardKey {
public:
    Key_C(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: C
class Key_D : public KeyboardKey {
public:
    Key_D(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: D
class Key_E : public KeyboardKey {
public:
    Key_E(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: E
class Key_F : public KeyboardKey {
public:
    Key_F(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F
class Key_G : public KeyboardKey {
public:
    Key_G(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: G
class Key_H : public KeyboardKey {
public:
    Key_H(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: H
class Key_I : public KeyboardKey {
public:
    Key_I(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: I
class Key_J : public KeyboardKey {
public:
    Key_J(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: J
class Key_K : public KeyboardKey {
public:
    Key_K(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: K
class Key_L : public KeyboardKey {
public:
    Key_L(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: L
class Key_M : public KeyboardKey {
public:
    Key_M(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: M
class Key_N : public KeyboardKey {
public:
    Key_N(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: N
class Key_O : public KeyboardKey {
public:
    Key_O(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: O
class Key_P : public KeyboardKey {
public:
    Key_P(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: P
class Key_Q : public KeyboardKey {
public:
    Key_Q(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Q
class Key_R : public KeyboardKey {
public:
    Key_R(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: R
class Key_S : public KeyboardKey {
public:
    Key_S(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: S
class Key_T : public KeyboardKey {
public:
    Key_T(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: T
class Key_U : public KeyboardKey {
public:
    Key_U(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: U
class Key_V : public KeyboardKey {
public:
    Key_V(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: V
class Key_W : public KeyboardKey {
public:
    Key_W(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: W
class Key_X : public KeyboardKey {
public:
    Key_X(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: X
class Key_Y : public KeyboardKey {
public:
    Key_Y(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Y
class Key_Z : public KeyboardKey {
public:
    Key_Z(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Z

class Key_LeftBracket : public KeyboardKey {
public:
    Key_LeftBracket(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: [
class Key_Backslash : public KeyboardKey {
public:
    Key_Backslash(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: '\'
class Key_RightBracket : public KeyboardKey {
public:
    Key_RightBracket(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: ]
class Key_Grave : public KeyboardKey {
public:
    Key_Grave(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: `

class Key_Space : public KeyboardKey {
public:
    Key_Space(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Space
class Key_Escape : public KeyboardKey {
public:
    Key_Escape(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Esc
class Key_Enter : public KeyboardKey {
public:
    Key_Enter(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Enter
class Key_Tab : public KeyboardKey {
public:
    Key_Tab(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Tab
class Key_Backspace : public KeyboardKey {
public:
    Key_Backspace(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Backspace
class Key_Insert : public KeyboardKey {
public:
    Key_Insert(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Ins
class Key_Delete : public KeyboardKey {
public:
    Key_Delete(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Del
class Key_Right : public KeyboardKey {
public:
    Key_Right(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Cursor right
class Key_Left : public KeyboardKey {
public:
    Key_Left(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Cursor left
class Key_Down : public KeyboardKey {
public:
    Key_Down(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Cursor down
class Key_Up : public KeyboardKey {
public:
    Key_Up(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Cursor up
class Key_PageUp : public KeyboardKey {
public:
    Key_PageUp(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Page up
class Key_PageDown : public KeyboardKey {
public:
    Key_PageDown(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Page down
class Key_Home : public KeyboardKey {
public:
    Key_Home(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Home
class Key_End : public KeyboardKey {
public:
    Key_End(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: End

class Key_CapsLock : public KeyboardKey {
public:
    Key_CapsLock(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Caps lock
class Key_ScrollLock : public KeyboardKey {
public:
    Key_ScrollLock(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Scroll lock
class Key_NumLock : public KeyboardKey {
public:
    Key_NumLock(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Num lock
class Key_PrintScreen : public KeyboardKey {
public:
    Key_PrintScreen(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Print screen
class Key_Pause : public KeyboardKey {
public:
    Key_Pause(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Pause

class Key_F1 : public KeyboardKey {
public:
    Key_F1(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F1
class Key_F2 : public KeyboardKey {
public:
    Key_F2(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F2
class Key_F3 : public KeyboardKey {
public:
    Key_F3(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F3
class Key_F4 : public KeyboardKey {
public:
    Key_F4(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F4
class Key_F5 : public KeyboardKey {
public:
    Key_F5(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F5
class Key_F6 : public KeyboardKey {
public:
    Key_F6(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F6
class Key_F7 : public KeyboardKey {
public:
    Key_F7(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F7
class Key_F8 : public KeyboardKey {
public:
    Key_F8(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F8
class Key_F9 : public KeyboardKey {
public:
    Key_F9(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F9
class Key_F10 : public KeyboardKey {
public:
    Key_F10(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F10
class Key_F11 : public KeyboardKey {
public:
    Key_F11(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F11
class Key_F12 : public KeyboardKey {
public:
    Key_F12(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: F12

class Key_LeftShift : public KeyboardKey {
public:
    Key_LeftShift(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Shift left
class Key_LeftControl : public KeyboardKey {
public:
    Key_LeftControl(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Control left
class Key_LeftAlt : public KeyboardKey {
public:
    Key_LeftAlt(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Alt left
class Key_LeftSuper : public KeyboardKey {
public:
    Key_LeftSuper(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Super left
class Key_RightShift : public KeyboardKey {
public:
    Key_RightShift(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Shift right
class Key_RightControl : public KeyboardKey {
public:
    Key_RightControl(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Control right
class Key_RightAlt : public KeyboardKey {
public:
    Key_RightAlt(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Alt right
class Key_RightSuper : public KeyboardKey {
public:
    Key_RightSuper(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: Super right
class Key_KBMenu : public KeyboardKey {
public:
    Key_KBMenu(state_t state)
        : KeyboardKey(state) {
    }
}; // Key: KB menu

// Keypad keys
class Key_KP_0 : public KeyboardKey {
public:
    Key_KP_0(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 0
class Key_KP_1 : public KeyboardKey {
public:
    Key_KP_1(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 1
class Key_KP_2 : public KeyboardKey {
public:
    Key_KP_2(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 2
class Key_KP_3 : public KeyboardKey {
public:
    Key_KP_3(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 3
class Key_KP_4 : public KeyboardKey {
public:
    Key_KP_4(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 4
class Key_KP_5 : public KeyboardKey {
public:
    Key_KP_5(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 5
class Key_KP_6 : public KeyboardKey {
public:
    Key_KP_6(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 6
class Key_KP_7 : public KeyboardKey {
public:
    Key_KP_7(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 7
class Key_KP_8 : public KeyboardKey {
public:
    Key_KP_8(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 8
class Key_KP_9 : public KeyboardKey {
public:
    Key_KP_9(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad 9
class Key_KP_Decimal : public KeyboardKey {
public:
    Key_KP_Decimal(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad .
class Key_KP_Divide : public KeyboardKey {
public:
    Key_KP_Divide(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad /
class Key_KP_Multiply : public KeyboardKey {
public:
    Key_KP_Multiply(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad *
class Key_KP_Subtract : public KeyboardKey {
public:
    Key_KP_Subtract(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad -
class Key_KP_Add : public KeyboardKey {
public:
    Key_KP_Add(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad +
class Key_KP_Enter : public KeyboardKey {
public:
    Key_KP_Enter(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad Enter
class Key_KP_Equal : public KeyboardKey {
public:
    Key_KP_Equal(state_t state)
        : KeyboardKey(state) {
    }
}; // Keypad =
} // namespace gengine::system::event::driver::input
