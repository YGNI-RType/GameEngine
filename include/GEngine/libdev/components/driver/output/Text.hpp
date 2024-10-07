/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Text.hpp
*/

#pragma once

#include <raylib.h>
#include <string>

#include "GEngine/libdev/Component.hpp"
#include "GEngine/libdev/components/driver/output/RaylibTypes.hpp"

namespace gengine::component::driver::output {
struct Text : public Component<Text> {
    std::string fontPath;
    std::string str;
    float fontSize;
    float spacing;
    Clr tint;

    Text(const std::string &fontPath, const std::string &str, const Clr &tint = BLACK, float spacing = 0)
        : fontPath(fontPath)
        , str(str)
        , fontSize(10)
        , spacing(spacing)
        , tint(tint) {
    }

    bool operator==(const Text &) const = default;
};
} // namespace gengine::component::driver::output
