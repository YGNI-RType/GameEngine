/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Monster.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"
#include <string>

#define DEFAULT_MONSTER_SPEED 1        // Speed multiplicator (default = 1)
#define DEFAULT_MONSTER_ATTACK_SPEED 3 // Shoot per second

namespace rtype::component {
struct Monster : public gengine::Component<Monster> {
    char name[32] = {0};
    float speed;
    float attackSpeed;

    Monster(const std::string &newName, float newSpeed = DEFAULT_MONSTER_SPEED,
            float newAttackSpeed = DEFAULT_MONSTER_ATTACK_SPEED)
        : speed(newSpeed)
        , attackSpeed(newAttackSpeed) {
        std::strncpy(name, newName.c_str(), 31);
    }
};

} // namespace rtype::component
