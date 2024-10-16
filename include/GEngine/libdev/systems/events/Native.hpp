/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Event
** ════════════════════════════════════════════════════════════════════════════
**  File        : Native.hpp
**  Create at   : 2024-10-15 05:22
**  Author      : AUTHOR
**  Description : These events are published natively by the engine itself.
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "GEngine/libdev/System.hpp"

namespace gengine::system::event {
class StartEngine : public Event {};
class StopEngine : public Event {};
} // namespace gengine::system::event
