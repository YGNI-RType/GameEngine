/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Player.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"
#include <string>

#define DEFAULT_SPEED 5
#define DEFAULT_ATTACK_SPEED 3 // Shoot per second

namespace rtype::component {
struct Player : public gengine::Component<Player> {
    // char name[32] = {0};
    float speed;
    float attackSpeed;
    int life = 3;

    // static void setScore(int score, )

    Player(float newSpeed = DEFAULT_SPEED, float newAttackSpeed = DEFAULT_ATTACK_SPEED)
        : speed(newSpeed)
        , attackSpeed(newAttackSpeed) {
        // std::strncpy(name, newName.c_str(), newName.size());
    }
};

} // namespace rtype::component
