/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Caterpillar.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

#define CATERPILLAR_DEFAULT_SPEED 4

namespace rtype::component {
struct Caterpillar : public gengine::Component<Caterpillar> {
    float speed;

    Caterpillar(float newSpeed = CATERPILLAR_DEFAULT_SPEED)
        : speed(newSpeed) {
    }
};
} // namespace rtype::component
