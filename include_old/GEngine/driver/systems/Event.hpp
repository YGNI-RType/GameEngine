/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Event.hpp
*/

#pragma once

#include "ecs/system/Base.hpp"

namespace gengine::driver::system {
class Event : public ecs::system::Base<Event> {
    Event(ecs::system::event::Bus eventBus)
        : Base<Event>(eventBus) { // TODO ne plus construire avec event bus mais forcé
                                  // le manager à la register a sa creation pourquoi pas
                                  // avec une méthod protected, ça éviterais d'avoir a
                                  // précesier la construction de Base<T>
    }

    void mainloop(event::MainLoop &e) override {
        // Keyboards events
        // mouse
        // os
    }
};
} // namespace gengine::driver::system
