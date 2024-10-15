/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Component
** ════════════════════════════════════════════════════════════════════════════
**  File        : Velocities.hpp
**  Create at   : 2024-10-15 05:29
**  Auteur      : AUTHOR
**  Description : These components allow you to manage movements linked to an
                    entity in a basic way, they are used by the Motion system
                    of libdev.
** ════════════════════════════════════════════════════════════════════════════
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
