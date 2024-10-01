/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Motions.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

namespace gengine::component {
struct Motion2D : public Component {
    float x, y;
    Motion2D(float x, float y) : x(x), y(y){};
};

struct Motion3D : public Component {
    float x, y, z;
    Motion3D(float x, float y, float z) : x(x), y(y), z(z){};
};
} // namespace gengine::component
