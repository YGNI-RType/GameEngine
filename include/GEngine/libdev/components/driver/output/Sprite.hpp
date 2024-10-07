/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Sprite.hpp
*/

#pragma once

#include <limits>
#include <raylib.h>
#include <string>

#include "GEngine/libdev/Component.hpp"
#include "GEngine/libdev/components/driver/output/RaylibTypes.hpp"

namespace gengine::component::driver::output {
struct Sprite : public Component<Sprite> {
    std::string txtPath; // The texture of the sprite
    Rect src;            // The portion of the texture to render (for sprite sheets/atlases)
    Clr tint;

    Sprite(const std::string &txtPath, const Rect &src, const Clr &tint = RAYWHITE)
        : txtPath(txtPath)
        , src(src)
        , tint(tint) {
    }
    Sprite(const std::string &txtPath, const Clr &tint = RAYWHITE)
        : txtPath(txtPath)
        , src(0.f, 0.f, std::numeric_limits<float>().max(), std::numeric_limits<float>().max())
        , tint(tint) {
    }

    bool operator==(const Sprite &) const = default;
};
} // namespace gengine::component::driver::output
