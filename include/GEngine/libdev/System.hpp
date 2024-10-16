/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** System.hpp
*/

#pragma once

#include "ecs/system/Base.hpp"
#include "ecs/system/event/Base.hpp"

namespace gengine {
template <typename T, class... DependTypes>
using System = ecs::system::Base<T, DependTypes...>;
using Event = ecs::system::event::Base;

template <typename T, typename EventType, class... DependTypes>
struct OnEventSystem : public System<OnEventSystem<T, EventType, DependTypes...>, DependTypes...> {
    void init(void) override {
        this->template subscribeToEvent<EventType>(&OnEventSystem::onEvent);
    }
    virtual void onEvent(EventType &e) = 0;
};
} // namespace gengine
