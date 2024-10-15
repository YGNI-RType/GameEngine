/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Component
** ════════════════════════════════════════════════════════════════════════════
**  File        : Shape.hpp
**  Create at   : 2024-10-15 05:26
**  Auteur      : AUTHOR
**  Description : DESCRIPTION // TODO popoche
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "module/raylib_safe.h"

#include "GEngine/libdev/Component.hpp"
#include "GEngine/libdev/components/driver/output/RaylibTypes.hpp"

namespace gengine::component::driver::output {
struct Rectangle : public Component<Rectangle> {
    int width;
    int height;
    Clr color;

    Rectangle(int width, int height, const Clr &&color)
        : width(width)
        , height(height)
        , color(color) {
    }

    bool operator==(const Rectangle &) const = default;
};

struct Circle : public Component<Circle> {
    int r;
    Clr color;

    Circle(int r, const Clr &&color)
        : r(r)
        , color(color) {
    }

    bool operator==(const Circle &) const = default;
};
} // namespace gengine::component::driver::output
