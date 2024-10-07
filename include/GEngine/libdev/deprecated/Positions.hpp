/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Positions.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

namespace gengine::component {
struct Position2D : public Component {
    float x, y;
    Position2D(float x, float y)
        : x(x)
        , y(y) {
    }
};

struct Position3D : public Component {
    float x, y, z;
    Position3D(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z) {
    }
};

struct Origin2D : public Component {
    float x, y;
    Origin2D(float x, float y)
        : x(x)
        , y(y) {
    }
};

struct Origin3D : public Component {
    float x, y, f;
    Origin3D(float x, float y)
        : x(x)
        , y(y) {
    }
};
} // namespace gengine::component
