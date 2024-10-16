/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Event
** ════════════════════════════════════════════════════════════════════════════
**  File        : Log.hpp
**  Create at   : 2024-10-15 05:19
**  Author      : AUTHOR
**  Description : This event is natively listened to by a system log and allows
                    any system to add content to the game log file.
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include <typeindex>

namespace gengine::system::event {
struct Log : public Event {
    std::string message;
    Log(const std::string &message)
        : message(message) {
    }
    Log(const std::string &&message)
        : message(message) {
    }
};
} // namespace gengine::system::event
