/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Color.hpp
*/

#pragma once

#include <raylib.h>

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
