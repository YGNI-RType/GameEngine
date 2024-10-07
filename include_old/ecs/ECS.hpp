/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** ECS.hpp
*/

#pragma once

#include <memory>

#include "ecs/component/Manager.hpp"
#include "ecs/entity/Manager.hpp"
#include "ecs/system/Manager.hpp"

#include "ecs/system/event/Base.hpp" // StartEngine MainLoop

namespace ecs {
class ECS : private entity::Manager, public component::Manager, public system::Manager {
public:
    ECS();

    template <typename... Components> entity::Entity spawnEntity(Components &&...components);

    void killEntity(entity::Entity entity);
};
} // namespace ecs

#include "ECS.inl"
