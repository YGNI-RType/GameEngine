/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Velocities.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

namespace gengine::component {
struct Velocity2D : public Component<Velocity2D> {
    float x, y;
    Velocity2D(float x, float y)
        : x(x)
        , y(y) {
    }

    bool operator==(const Velocity2D &) const = default;
};

struct Velocity3D : public Component<Velocity3D> {
    float x, y, z;
    Velocity3D(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z) {
    }

    bool operator==(const Velocity3D &) const = default;
};
} // namespace gengine::component
