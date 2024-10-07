/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Drawable.hpp
*/

#pragma once

#include <cstdlib>

#include "GEngine/libdev/Component.hpp"

namespace gengine::component::driver::output {
struct Drawable : public Component<Drawable> {
    std::size_t zIndex;
    Drawable(std::size_t zIndex)
        : zIndex(zIndex) {
    }

    bool operator==(const Drawable &) const = default;
};
} // namespace gengine::component::driver::output