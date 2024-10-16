/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Window.hpp
*/

#pragma once

#include <string>

#include "GEngine/libdev/Component.hpp"

namespace gengine::component::driver::output {
struct Window : public gengine::Component {
    int width;
    int height;
    std::string title;

    Window(int width = 1080, int height = 720, const std::string &title = "window")
        : width(width)
        , height(height)
        , title(title) {
    }
    Window(int width = 1080, int height = 720, const std::string &&title = "window")
        : width(width)
        , height(height)
        , title(title) {
    }
};
} // namespace gengine::component::driver::output
