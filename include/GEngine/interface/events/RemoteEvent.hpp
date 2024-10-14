/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** RemoteEvent.hpp
*/

#pragma once

#include "GEngine/interface/components/RemoteDriver.hpp"
#include "GEngine/libdev/System.hpp"

namespace gengine::interface::network::event {

template <class T>
class RemoteEvent : public Event {
public:
    explicit RemoteEvent(T &event, component::RemoteDriver &remote)
        : remote(remote)
        , m_event(event) {
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

    component::RemoteDriver remote;

private:
    T m_event;
};
} // namespace gengine::interface::network::event