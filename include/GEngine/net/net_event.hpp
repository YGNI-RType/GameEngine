/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event
*/

#pragma once

#include <memory>

namespace Network
{
    enum EventType
    {
        CONNECT,
        DISCONNECT,
        MESSAGE,
        PINGs
    };

    struct EventInfoHeader {
        EventType type;
    };

    template <typename T>
    struct EventInfo : public EventInfoHeader {
        std::unique_ptr<T> data;
    };

    class EventManager {
        public:
            EventManager() = default;
            ~EventManager() = default;

            void addEvent(EventType type, std::unique_ptr<EventInfoHeader> data);
            void handleEvents(void);
    };
} // namespace Network
