/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Entity.hpp
*/

#include "ecs/entity/Entity.hpp"

namespace gengine {
/**
 * @brief A type alias representing an entity in the GEngine framework.
 *
 * This alias simplifies the usage of entities by providing a more specific name
 * that integrates the ECS (Entity-Component-System) architecture from the
 * ecs::entity namespace.
 *
 * @typedef Entity
 */
using Entity = ecs::entity::Entity;
} // namespace gengine