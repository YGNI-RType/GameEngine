/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Shape.hpp
*/

#pragma once

#include <raylib.h>

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
