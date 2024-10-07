/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** HitBox.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

namespace gengine::component {
struct HitBoxSquare2D : public Component<HitBoxSquare2D> {
    int width, height;
    HitBoxSquare2D(int width, int height)
        : width(width)
        , height(height) {
    }

    bool operator==(const HitBoxSquare2D &) const = default;
};

struct HitBoxSquare3D : public Component<HitBoxSquare3D> {
    int width, height, depth;
    HitBoxSquare3D(int width, int height)
        : width(width)
        , height(height) {
    }

    bool operator==(const HitBoxSquare3D &) const = default;
};

struct HitBoxCircle2D : public Component<HitBoxCircle2D> {
    int radius;
    HitBoxCircle2D(int radius)
        : radius(radius) {
    }

    bool operator==(const HitBoxCircle2D &) const = default;
};

using HitBoxCircle3D = HitBoxCircle2D;
} // namespace gengine::component
