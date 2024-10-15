/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Shoot.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"

namespace rtype::event {
struct Shoot : public gengine::Event {
    enum State { REST = 0, CHARGING };

    State state;

    Shoot(State state)
        : state(state) {
    }
};
} // namespace rtype::event
