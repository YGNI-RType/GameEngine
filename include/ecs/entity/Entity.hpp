/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Entity.hpp
*/

#pragma once

#include <cstdlib>

namespace ecs::entity {
/**
 * @brief A type alias representing an entity in the ECS (Entity-Component-System) architecture.
 *
 * Entities are represented as unique identifiers (typically an integer or index).
 * These identifiers are used to associate components with entities in the ECS system.
 *
 * @typedef Entity
 */
typedef std::size_t Entity;
} // namespace ecs::entity
