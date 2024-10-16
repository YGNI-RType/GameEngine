/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Bullet.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

#include <cstring>

namespace rtype::component {
struct Bullet : public gengine::Component<Bullet> {
    Bullet(std::string fromString, bool isBeam = false)
        : isBeam(isBeam) {
        std::strncpy(from, fromString.c_str(), 36);
        from[36] = '\0';
    }

    char from[37];
    bool isBeam = false;
};
} // namespace rtype::component
