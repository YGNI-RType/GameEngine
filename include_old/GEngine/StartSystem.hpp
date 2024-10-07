// /*
// ** EPITECH PROJECT, 2024
// ** B-CPP-500-LYN-5-1-rtype-basile.fouquet
// ** File description:
// ** StartSystem.hpp
// */

// #pragma once

// #include "ecs/system/Base.hpp"
// #include "ecs/system/event/Base.hpp"

// template <class Derived, typename EventType, class ...DependTypes>
// class OnEventSystem: public ecs::system::Base<Derived, DependTypes...> {
// public:
//     void init(void) override {
//         subscribeToEvent<EventType>(&Derived::onEvent);
//     }

//     void onEvent(EventType &) = 0;
// };

// class MainLoop: public OnEventSystem<MainLoop, event::MainLoop, int>
// {
//     void onEvnet
// }