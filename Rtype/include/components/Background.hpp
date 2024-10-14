/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Background.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

#define DEFAULT_BACKGROUND_SPEED -100 // Speed multiplicator (default = -100)

namespace rtype::component {
struct Background : public gengine::Component<Background> {
    float speed;

    Background(float newSpeed = DEFAULT_BACKGROUND_SPEED)
        : speed(newSpeed) {
    }
};
} // namespace rtype::component
