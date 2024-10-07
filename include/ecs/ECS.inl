/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** ECS.inl
*/

#pragma once

#include "ecs/entity/Manager.hpp"

namespace ecs {
template <typename... Components>
entity::Entity ECS::spawnEntity(Components &&...components) {
    entity::Entity entity = createEntity();
    (setComponent(entity, std::forward<Components>(components)), ...);
    return entity;
}
} // namespace ecs
