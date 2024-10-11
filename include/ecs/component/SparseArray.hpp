/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** SparseArray.hpp
*/

#pragma once

#include <any>
#include <typeindex>
#include <vector>

#include "ecs/entity/Entity.hpp"

namespace ecs::component {
/**
 * @brief A tuple representing information about a component in the ECS system.
 *
 * This tuple stores an entity, the type of the component, and the actual component data.
 * It is typically used for passing or storing information about components in a generic way.
 *
 * @typedef component_info_t
 * @param entity::Entity The entity to which the component belongs.
 * @param std::type_index A reference to the type information of the component.
 * @param bool Boolean indicating if the component has been set or unset.
 * @param std::any A generic container that holds the component data if set.
 */
using component_info_t = std::tuple<entity::Entity, const std::type_index &, bool, const std::any>;

/**
 * @brief A sparse array structure for managing components in an ECS system.
 *
 * This class efficiently stores components associated with entities, using a dense array
 * for quick iteration and a sparse array for fast lookups by entity.
 *
 * @tparam Component The type of component that the array will store.
 */
template <class Component>
class SparseArray { // TODO std::optional getComponents(entity &from) if more efficient + get const entity
public:
    /**
     * @brief Default constructor.
     */
    SparseArray() = default;

    /**
     * @brief Default destructor.
     */
    ~SparseArray() = default;

    /**
     * @brief Reserves space for components associated with entities up to a given capacity.
     *
     * @param capacity The number of entities for which to reserve space.
     */
    void reserve(entity::Entity capacity);

    /**
     * @brief Inserts a component for a given entity.
     *
     * If the entity already has this thype of component, it replaces it.
     *
     * @param entity The entity to which the component belongs.
     * @param component The component to insert.
     */
    void insert(entity::Entity entity, const Component &component);

    /**
     * @brief Emplaces a component for a given entity using constructor parameters.
     *
     * Constructs the component in place using the provided parameters, avoiding a copy or move.
     * If the entity already has this thype of component, it replaces it.
     *
     * @tparam Params Variadic template parameter pack used to forward to the component's constructor.
     * @param entity The entity to which the component belongs.
     * @param p The parameters to forward to the component's constructor.
     */
    template <typename... Params>
    void emplace(entity::Entity entity, Params &&...p);

    /**
     * @brief Erases the component associated with a given entity.
     *
     * @param entity The entity whose component should be removed.
     */
    void erase(entity::Entity entity);

    /**
     * @brief Checks if a component exists for a given entity.
     *
     * @param entity The entity to check for a component.
     * @return True if a component exists for the entity, false otherwise.
     */
    bool contains(entity::Entity entity) const;

    /**
     * @brief Retrieves a reference to the component associated with a given entity.
     *
     * @param entity The entity whose component should be retrieved.
     * @return A reference to the component.
     * @throws std::out_of_range if the entity does not have an associated component.
     */
    Component &get(entity::Entity entity);

    /**
     * @brief Retrieves a const reference to the component associated with a given entity.
     *
     * @param entity The entity whose component should be retrieved.
     * @return A const reference to the component.
     * @throws std::out_of_range if the entity does not have an associated component.
     */
    const Component &get(entity::Entity entity) const;

    /**
     * @brief Returns the number of components currently stored in the dense array.
     *
     * @return The number of components.
     */
    std::size_t size() const;

    /**
     * @brief Returns the current reserved capacity of the sparse array.
     *
     * @return The reserved capacity for storing components.
     */
    std::size_t reserved() const;

    /**
     * @brief Type definition for an iterator over the dense array of entity-component pairs.
     */
    using dense_iterator = typename std::vector<std::pair<entity::Entity, Component>>::iterator;

    /**
     * @brief Type definition for a const iterator over the dense array of entity-component pairs.
     */
    using dense_const_iterator = typename std::vector<std::pair<entity::Entity, Component>>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the dense array.
     *
     * @return An iterator to the first element in the dense array.
     */
    dense_iterator begin();

    /**
     * @brief Returns an iterator to the end of the dense array.
     *
     * @return An iterator to the element following the last element in the dense array.
     */
    dense_iterator end();

    /**
     * @brief Returns a const iterator to the beginning of the dense array.
     *
     * @return A const iterator to the first element in the dense array.
     */
    dense_const_iterator cbegin() const;

    /**
     * @brief Returns a const iterator to the end of the dense array.
     *
     * @return A const iterator to the element following the last element in the dense array.
     */
    dense_const_iterator cend() const;

private:
    /**
     * @brief A constant representing an invalid index.
     *
     * Used to indicate that an entity does not have an associated component.
     */
    static constexpr std::size_t invalid_index = std::size_t(-1);

    /**
     * @brief Sparse array for fast lookups by entity.
     *
     * Maps entity IDs to indices in the dense array.
     */
    std::vector<entity::Entity> m_sparse;

    /**
     * @brief Dense array for storing entity-component pairs.
     *
     * Components are stored alongside their associated entities for quick iteration.
     */
    std::vector<std::pair<entity::Entity, Component>> m_dense;
};
} // namespace ecs::component

#include "SparseArray.inl"
