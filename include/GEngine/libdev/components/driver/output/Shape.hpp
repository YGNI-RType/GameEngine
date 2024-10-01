/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Shape.hpp
*/

#pragma once

#include <raylib.h>

#include "GEngine/libdev/Component.hpp"

namespace gengine::component::driver::output {
struct Rectangle : public gengine::Component {
    int width;
    int height;
    Color color;

    Rectangle(int width, int height, const Color &&color) : width(width), height(height), color(color) {};
    // Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {};
};

struct Circle : public gengine::Component {
    int r;
    Color color;

    Circle(int r, const Color &&color) : r(r), color(color) {};
    // Circle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {};
};
} // namespace gengine::component::driver::output
