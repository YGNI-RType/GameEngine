/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Score.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"

namespace rtype::component {
struct Score : public gengine::Component<Score> {
    int score = 0;

    Score(int score)
        : score(score) {
    }
};
} // namespace rtype::component
