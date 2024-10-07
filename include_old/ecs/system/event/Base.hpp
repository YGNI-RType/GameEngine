/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Base.hpp
*/

#pragma once

#include <iostream>
#include <vector>

namespace ecs::system::event {
/**
 * @brief Base class for all events.
 *
 * This is the base class from which all specific event types should derive.
 * It provides a default constructor, destructor, and copy constructor.
 * This class is meant to be used polymorphically for event handling.
 */
class Base {
public:
    /**
     * @brief Default constructor.
     */
    Base() = default;

    /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup of derived classes.
     */
    virtual ~Base() = default;

    /**
     * @brief Default copy constructor.
     */
    Base(const Base &) = default;
};

} // namespace ecs::system::event
