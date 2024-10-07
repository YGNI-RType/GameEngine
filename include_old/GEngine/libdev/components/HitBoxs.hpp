/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** HitBox.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

namespace gengine::component {
struct HitBoxSquare2D : public Component {
    int width, height;
    HitBoxSquare2D(int width, int height) : width(width), height(height) {}
};

struct HitBoxSquare3D : public Component {
    int width, height, depth;
    HitBoxSquare3D(int width, int height) : width(width), height(height) {}
};

struct HitBoxCircle2D : public Component {
    int radius;
    HitBoxCircle2D(int radius) : radius(radius) {}
};

using HitBoxCircle3D = HitBoxCircle2D;
} // namespace gengine::component
