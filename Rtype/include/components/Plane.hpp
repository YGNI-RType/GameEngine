/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Plane.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

#define PLANE_DEFAULT_SPEED 5

namespace rtype::component {
struct Plane : public gengine::Component<Plane> {
    float speed;

    Plane(float newSpeed = PLANE_DEFAULT_SPEED)
        : speed(newSpeed) {
    }
};
} // namespace rtype::component
