/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Sprite.hpp
*/

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
struct Sprite : public gengine::Component {
    Texture texture; // The texture of the sprite
    ::Rectangle src; // The portion of the texture to render (for sprite sheets/atlases)
    Color tint;

    Sprite(const Texture &texture, const ::Rectangle &src, const Color &tint = RAYWHITE)
        : texture(texture), src(src), tint(tint) {};
    Sprite(const Texture &texture, const Color &tint = RAYWHITE) : texture(texture), tint(tint) {
        src = {0, 0, src.width, src.height};
    };
};
} // namespace gengine::component::driver::output
