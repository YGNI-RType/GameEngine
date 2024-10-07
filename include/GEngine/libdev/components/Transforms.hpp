/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Transform.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"
#include "GEngine/libdev/tools/Math.hpp"

namespace gengine::component {
struct Transform2D : public Component<Transform2D> {
    Vect2 pos;
    Vect2 scale;
    float rotation; // degree
    Transform2D(const Vect2 &pos, const Vect2 &scale = {1, 1}, float rotation = 0.f)
        : pos(pos)
        , scale(scale)
        , rotation(rotation) {
    }

    bool operator==(const Transform2D &) const = default;
};

struct Transform3D : public Component<Transform3D> {
    Vect3 pos;
    Vect3 scale;
    float rotation;
    Transform3D(const Vect3 &pos, const Vect3 &scale = {1, 1}, float rotation = 0.f)
        : pos(pos)
        , scale(scale)
        , rotation(rotation) {
    }

    bool operator==(const Transform3D &) const = default;
};
} // namespace gengine::component
