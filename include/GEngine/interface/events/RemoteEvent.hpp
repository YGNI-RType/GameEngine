/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** RemoteEvent.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"

namespace gengine::interface::network::event {

template <class T>
class RemoteEvent : public Event {
public:
    explicit RemoteEvent(T &event)
        : m_event(event) {
    }

    T *operator->() {
        return &m_event;
    }

    const T *operator->() const {
        return &m_event;
    }

    T &operator*() {
        return m_event;
    }

    const T &operator*() const {
        return m_event;
    }

private:
    T m_event;
    std::uint64_t m_clientId;
};
} // namespace gengine::interface::network::event