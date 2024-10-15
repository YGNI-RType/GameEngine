/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Transform.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

namespace gengine::component {
struct SpanLife : public Component<SpanLife> {
    float time; // in seconds // TODO tick (same for animations)
    SpanLife(float time)
        : time(time) {
    }

    bool operator==(const SpanLife &) const = default;
};
} // namespace gengine::component
