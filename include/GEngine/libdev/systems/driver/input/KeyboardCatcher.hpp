/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : KeyboardCatcher.hpp
**  Create at   : 2024-10-15 04:58
**  Author      : AUTHOR
**  Description : This system is dedicated to the DriverEngine, it must with
                    the raylib publish all the events linked to the keys of
                    the keyboard.
** ═══════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "module/raylib_safe.h"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/libdev/systems/events/RenderLoop.hpp"
#include "GEngine/libdev/systems/events/driver/input/Keyboard.hpp"

namespace gengine::system::driver::input {
using InputState = gengine::system::event::driver::input::state_t;
class KeyboardCatcher : public gengine::System<KeyboardCatcher> {
public:
    void init(void) override;

    void onMainLoop(gengine::system::event::RenderLoop &e);

private:
    void processKeyInput(int key, InputState state);
};

KeyboardKey &operator++(KeyboardKey &key);

using KeyApostropheEvent = gengine::system::event::driver::input::Key_Apostrophe;
using KeyCommaEvent = gengine::system::event::driver::input::Key_Comma;
using KeyMinusEvent = gengine::system::event::driver::input::Key_Minus;
using KeyPeriodEvent = gengine::system::event::driver::input::Key_Period;
using KeySlashEvent = gengine::system::event::driver::input::Key_Slash;
using KeyZeroEvent = gengine::system::event::driver::input::Key_Zero;
using KeyOneEvent = gengine::system::event::driver::input::Key_One;
using KeyTwoEvent = gengine::system::event::driver::input::Key_Two;
using KeyThreeEvent = gengine::system::event::driver::input::Key_Three;
using KeyFourEvent = gengine::system::event::driver::input::Key_Four;
using KeyFiveEvent = gengine::system::event::driver::input::Key_Five;
using KeySixEvent = gengine::system::event::driver::input::Key_Six;
using KeySevenEvent = gengine::system::event::driver::input::Key_Seven;
using KeyEightEvent = gengine::system::event::driver::input::Key_Eight;
using KeyNineEvent = gengine::system::event::driver::input::Key_Nine;
using KeySemicolonEvent = gengine::system::event::driver::input::Key_Semicolon;
using KeyEqualEvent = gengine::system::event::driver::input::Key_Equal;
using KeyAEvent = gengine::system::event::driver::input::Key_A;
using KeyBEvent = gengine::system::event::driver::input::Key_B;
using KeyCEvent = gengine::system::event::driver::input::Key_C;
using KeyDEvent = gengine::system::event::driver::input::Key_D;
using KeyEEvent = gengine::system::event::driver::input::Key_E;
using KeyFEvent = gengine::system::event::driver::input::Key_F;
using KeyGEvent = gengine::system::event::driver::input::Key_G;
using KeyHEvent = gengine::system::event::driver::input::Key_H;
using KeyIEvent = gengine::system::event::driver::input::Key_I;
using KeyJEvent = gengine::system::event::driver::input::Key_J;
using KeyKEvent = gengine::system::event::driver::input::Key_K;
using KeyLEvent = gengine::system::event::driver::input::Key_L;
using KeyMEvent = gengine::system::event::driver::input::Key_M;
using KeyNEvent = gengine::system::event::driver::input::Key_N;
using KeyOEvent = gengine::system::event::driver::input::Key_O;
using KeyPEvent = gengine::system::event::driver::input::Key_P;
using KeyQEvent = gengine::system::event::driver::input::Key_Q;
using KeyREvent = gengine::system::event::driver::input::Key_R;
using KeySEvent = gengine::system::event::driver::input::Key_S;
using KeyTEvent = gengine::system::event::driver::input::Key_T;
using KeyUEvent = gengine::system::event::driver::input::Key_U;
using KeyVEvent = gengine::system::event::driver::input::Key_V;
using KeyWEvent = gengine::system::event::driver::input::Key_W;
using KeyXEvent = gengine::system::event::driver::input::Key_X;
using KeyYEvent = gengine::system::event::driver::input::Key_Y;
using KeyZEvent = gengine::system::event::driver::input::Key_Z;
using KeyLeftBracketEvent = gengine::system::event::driver::input::Key_LeftBracket;
using KeyBackslashEvent = gengine::system::event::driver::input::Key_Backslash;
using KeyRightBracketEvent = gengine::system::event::driver::input::Key_RightBracket;
using KeyGraveEvent = gengine::system::event::driver::input::Key_Grave;
using KeySpaceEvent = gengine::system::event::driver::input::Key_Space;
using KeyEscapeEvent = gengine::system::event::driver::input::Key_Escape;
using KeyEnterEvent = gengine::system::event::driver::input::Key_Enter;
using KeyTabEvent = gengine::system::event::driver::input::Key_Tab;
using KeyBackspaceEvent = gengine::system::event::driver::input::Key_Backspace;
using KeyInsertEvent = gengine::system::event::driver::input::Key_Insert;
using KeyDeleteEvent = gengine::system::event::driver::input::Key_Delete;
using KeyRightEvent = gengine::system::event::driver::input::Key_Right;
using KeyLeftEvent = gengine::system::event::driver::input::Key_Left;
using KeyDownEvent = gengine::system::event::driver::input::Key_Down;
using KeyUpEvent = gengine::system::event::driver::input::Key_Up;
using KeyPageUpEvent = gengine::system::event::driver::input::Key_PageUp;
using KeyPageDownEvent = gengine::system::event::driver::input::Key_PageDown;
using KeyHomeEvent = gengine::system::event::driver::input::Key_Home;
using KeyEndEvent = gengine::system::event::driver::input::Key_End;
using KeyCapsLockEvent = gengine::system::event::driver::input::Key_CapsLock;
using KeyScrollLockEvent = gengine::system::event::driver::input::Key_ScrollLock;
using KeyNumLockEvent = gengine::system::event::driver::input::Key_NumLock;
using KeyPrintScreenEvent = gengine::system::event::driver::input::Key_PrintScreen;
using KeyPauseEvent = gengine::system::event::driver::input::Key_Pause;
using KeyF1Event = gengine::system::event::driver::input::Key_F1;
using KeyF2Event = gengine::system::event::driver::input::Key_F2;
using KeyF3Event = gengine::system::event::driver::input::Key_F3;
using KeyF4Event = gengine::system::event::driver::input::Key_F4;
using KeyF5Event = gengine::system::event::driver::input::Key_F5;
using KeyF6Event = gengine::system::event::driver::input::Key_F6;
using KeyF7Event = gengine::system::event::driver::input::Key_F7;
using KeyF8Event = gengine::system::event::driver::input::Key_F8;
using KeyF9Event = gengine::system::event::driver::input::Key_F9;
using KeyF10Event = gengine::system::event::driver::input::Key_F10;
using KeyF11Event = gengine::system::event::driver::input::Key_F11;
using KeyF12Event = gengine::system::event::driver::input::Key_F12;
using KeyLeftShiftEvent = gengine::system::event::driver::input::Key_LeftShift;
using KeyLeftControlEvent = gengine::system::event::driver::input::Key_LeftControl;
using KeyLeftAltEvent = gengine::system::event::driver::input::Key_LeftAlt;
using KeyLeftSuperEvent = gengine::system::event::driver::input::Key_LeftSuper;
using KeyRightShiftEvent = gengine::system::event::driver::input::Key_RightShift;
using KeyRightControlEvent = gengine::system::event::driver::input::Key_RightControl;
using KeyRightAltEvent = gengine::system::event::driver::input::Key_RightAlt;
using KeyRightSuperEvent = gengine::system::event::driver::input::Key_RightSuper;
using KeyKBMenuEvent = gengine::system::event::driver::input::Key_KBMenu;
using KeyKP0Event = gengine::system::event::driver::input::Key_KP_0;
using KeyKP1Event = gengine::system::event::driver::input::Key_KP_1;
using KeyKP2Event = gengine::system::event::driver::input::Key_KP_2;
using KeyKP3Event = gengine::system::event::driver::input::Key_KP_3;
using KeyKP4Event = gengine::system::event::driver::input::Key_KP_4;
using KeyKP5Event = gengine::system::event::driver::input::Key_KP_5;
using KeyKP6Event = gengine::system::event::driver::input::Key_KP_6;
using KeyKP7Event = gengine::system::event::driver::input::Key_KP_7;
using KeyKP8Event = gengine::system::event::driver::input::Key_KP_8;
using KeyKP9Event = gengine::system::event::driver::input::Key_KP_9;
using KeyKPDecimalEvent = gengine::system::event::driver::input::Key_KP_Decimal;
using KeyKPDivideEvent = gengine::system::event::driver::input::Key_KP_Divide;
using KeyKPMultiplyEvent = gengine::system::event::driver::input::Key_KP_Multiply;
using KeyKPSubtractEvent = gengine::system::event::driver::input::Key_KP_Subtract;
using KeyKPAddEvent = gengine::system::event::driver::input::Key_KP_Add;
using KeyKPEnterEvent = gengine::system::event::driver::input::Key_KP_Enter;
using KeyKPEqualEvent = gengine::system::event::driver::input::Key_KP_Equal;
} // namespace gengine::system::driver::input