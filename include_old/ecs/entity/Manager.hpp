/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** entity::Manager.hpp
*/

#pragma once

#include <queue>

#include "ecs/entity/Entity.hpp"

namespace ecs::entity {
class Manager {
public:
    Manager();

    Entity createEntity();
    void destroyEntity(Entity dead);

private:
    std::size_t m_size;
    std::queue<Entity> m_available;
};
} // namespace ecs::entity
