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

namespace ecs {
/**
 * @brief A central class for managing the Entity-Component-System (ECS) architecture.
 *
 * This class integrates the functionality of managing entities, components, and systems.
 * It provides methods to spawn and kill entities while handling component assignment.
 *
 * The `ECS` class privately inherits from `entity::Manager` and publicly inherits from `component::Manager`
 * and `system::Manager`, offering comprehensive control over the ECS lifecycle.
 */
class ECS : private entity::Manager, public component::Manager, public system::Manager {
public:
    /**
     * @brief Constructs an ECS instance.
     *
     * Initializes the ECS system by constructing the entity, component, and system managers.
     */
    ECS(void);

    /**
     * @brief Spawns a new entity and assigns the provided components to it.
     *
     * This method creates a new entity in the ECS and assigns a variable number of components to it.
     * Components can be passed as arguments and will be associated with the created entity.
     *
     * @tparam Components Variadic template parameter for the types of components to be assigned.
     * @param components The components to assign to the entity, passed as arguments.
     * @return The newly created entity.
     */
    template <typename... Components>
    entity::Entity spawnEntity(Components &&...components);

    /**
     * @brief Kills an entity, removing it from the ECS.
     *
     * This method destroys the given entity, marking it for removal from the system.
     * All components associated with the entity are also removed.
     *
     * @param entity The entity to be killed.
     */
    void killEntity(entity::Entity entity);
};
} // namespace ecs

#include "ECS.inl"
