
/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** DestroyOnCollision.cpp
*/

#include "systems/DestroyOnCollision.hpp"

namespace rtype::system {
void DestroyOnCollision::init(void) {
    subscribeToEvent<gengine::system::event::Collsion>(&DestroyOnCollision::destroyMonster);
    subscribeToEvent<gengine::system::event::Collsion>(&DestroyOnCollision::destroyPlayer);
}

void DestroyOnCollision::destroyMonster(gengine::system::event::Collsion &e) {
    auto &monsters = getComponents<component::Monster>();
    auto &bullets = getComponents<component::Bullet>();

    for (auto [entity1, monster] : monsters) {
        for (auto [entity2, bullet] : bullets) {
            if ((e.entity1 == entity1 || e.entity2 == entity1) && (e.entity1 == entity2 || e.entity2 == entity2)) {
                killEntity(entity1);
                killEntity(entity2);
            }
        }
    }
}

void DestroyOnCollision::destroyPlayer(gengine::system::event::Collsion &e) {
    auto &players = getComponents<component::Player>();
    auto &monsters = getComponents<component::Monster>();

    for (auto [entity1, monster] : players) {
        for (auto [entity2, bullet] : monsters)
            if ((e.entity1 == entity1 || e.entity2 == entity1) && (e.entity1 == entity2 || e.entity2 == entity2))
                killEntity(entity1);
    }
}
} // namespace rtype::system
