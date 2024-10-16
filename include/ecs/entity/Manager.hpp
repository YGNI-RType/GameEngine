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
/**
 * @brief Manages the creation and destruction of entities in the ECS system.
 *
 * The Manager class handles the lifecycle of entities, allowing for the creation of new entities
 * and the recycling of destroyed entities for efficient memory management.
 */
class Manager {
public:
    /**
     * @brief Constructs an Entity Manager.
     *
     * Initializes the manager for handling entity creation and destruction.
     */
    Manager();

    /**
     * @brief Creates a new entity.
     *
     * If there are any previously destroyed entities, they are reused; otherwise, a new entity
     * identifier is generated.
     *
     * @return The newly created entity.
     */
    Entity createEntity();

    /**
     * @brief Destroys an entity.
     *
     * Marks an entity as destroyed, making its identifier available for reuse.
     *
     * @param dead The entity to be destroyed.
     */
    void destroyEntity(Entity dead);

private:
    /// The current size of the entity pool, used to generate new entity IDs.
    std::size_t m_size;

    /// A queue of available (recycled) entity IDs.
    std::queue<Entity> m_available;
};
} // namespace ecs::entity
