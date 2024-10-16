/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Component.hpp
*/

#pragma once

#include "ecs/component/IsComponent.hpp"
#include "ecs/component/Iterator.hpp"

#include <utility>

namespace gengine {
/**
 * @brief A type alias for ECS components using the IsComponent CRTP base structure.
 *
 * This alias is used to simplify the definition of components in the ECS system by
 * inheriting from the `ecs::component::IsComponent` base class.
 *
 * @tparam Derived The component type that inherits from `ecs::component::IsComponent`.
 */
template <class Derived>
using Component = ecs::component::IsComponent<Derived>;

/**
 * @brief A traits structure used to extract the element type from a SparseArray.
 *
 * This template specialization helps in retrieving the component type that a SparseArray holds.
 * It allows for generic code to work with different types of `SparseArray` instances.
 *
 * @tparam SparseArrayType The type of SparseArray (unspecialized version).
 */
template <typename SparseArrayType>
struct SparseArrayTraits;

/**
 * @brief Specialization of SparseArrayTraits for ecs::component::SparseArray.
 *
 * This specialization extracts the type of the element stored in the SparseArray.
 *
 * @tparam Element The type of element stored in the SparseArray.
 */
template <typename Element>
struct SparseArrayTraits<ecs::component::SparseArray<Element>> {
    /// The type of the element stored in the SparseArray.
    using type = Element;
};

/**
 * @brief A utility function that zips multiple SparseArray instances together.
 *
 * This function creates a Zipper object that allows for iteration over multiple `SparseArray` instances in parallel.
 * The Zipper only iterates over entities that are present in all arrays and provides access to their components.
 *
 * @tparam SparseArrays The types of the SparseArray instances to be zipped.
 * @param s The SparseArray instances to zip together.
 * @return A Zipper object for iterating over the entities and their associated components.
 */
template <class... SparseArrays>
ecs::component::Zipper<typename SparseArrayTraits<SparseArrays>::type...> Zip(SparseArrays &...s) {
    return ecs::component::Zipper<typename SparseArrayTraits<SparseArrays>::type...>(s...);
}
} // namespace gengine
