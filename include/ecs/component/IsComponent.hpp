/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** IsComponent.hpp
*/

#pragma once

#include <concepts>

namespace ecs::component {

// TODO Concept to check if a type has operator==
// template <typename T>
// concept EqualityComparable = requires(const T &a, const T &b) {
//     { a == b } -> std::convertible_to<bool>;
// };

/**
 * @brief A CRTP (Curiously Recurring Template Pattern) base structure to define component types in the ECS system.
 *
 * This structure ensures that components derived from it implement equality comparison.
 * It serves as a base class that enforces component behavior, allowing comparison operations between components.
 *
 * @tparam Derived The component type that inherits from this structure.
 */
template <typename Derived>
struct IsComponent {
    /**
     * @brief Equality comparison operator for components.
     *
     * This operator compares two instances of `IsComponent`-derived components to check if they are equal.
     * The `= default` specifier ensures that the comparison uses the default member-wise equality.
     *
     * @param other The other `IsComponent`-derived instance to compare with.
     * @return True if the two components are equal, false otherwise.
     */
    bool operator==(const IsComponent<Derived> &) const = default;
};
} // namespace ecs::component
