/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Component
** ════════════════════════════════════════════════════════════════════════════
**  File        : RaylibTypes.hpp
**  Create at   : 2024-10-15 05:25
**  Auteur      : AUTHOR
**  Description : Usual file
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "module/raylib_safe.h"

namespace gengine::component::driver::output {
struct Clr {
    unsigned char r; // Color red value
    unsigned char g; // Color green value
    unsigned char b; // Color blue value
    unsigned char a; // Color alpha value

    Clr(const Color &color)
        : r(color.r)
        , g(color.g)
        , b(color.b)
        , a(color.a) {
    }

    operator Color() const {
        return Color{r, g, b, a};
    }

    bool operator==(const Clr &) const = default;
}; // Color translater from raylib to GEngine

struct Rect {
    float x;      // Rectangle top-left corner position x
    float y;      // Rectangle top-left corner position y
    float width;  // Rectangle width
    float height; // Rectangle height

    Rect(const ::Rectangle &rect)
        : x(rect.x)
        , y(rect.y)
        , width(rect.width)
        , height(rect.height) {
    }
    Rect(float x, float y, float width, float height)
        : x(x)
        , y(y)
        , width(width)
        , height(height) {
    }

    operator ::Rectangle() const {
        return ::Rectangle{x, y, width, height};
    }

    bool operator==(const Rect &) const = default;
}; // Color translater from raylib to GEngine

} // namespace gengine::component::driver::output
