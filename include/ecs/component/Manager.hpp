/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** component::Manager.hpp
*/

#pragma once

#include <any>
#include <cstring>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "ecs/component/IsComponent.hpp"
#include "ecs/component/Iterator.hpp"
#include "ecs/component/SparseArray.hpp"
#include "exceptions/Base.hpp"

namespace ecs::component {
/**
 * @brief Manages the registration, setting, and destruction of components for entities in an ECS system.
 *
 * We can have many types of Component, this is why we handle std::any.
 */
class Manager {
public:
    /**
     * @brief Type alias for a function responsible for destroying components of an entity.
     * @param entity The entity whose component should be destroyed.
     */
    typedef std::function<void(entity::Entity)> destroyer_t;

    /**
     * @brief Type alias for a function responsible for setting a component to an entity.
     * @param entity The entity whose component is being set.
     * @param component The component data to set (as std::any).
     */
    typedef std::function<void(entity::Entity, const std::any &)> setter_t;

    /**
     * @brief Type alias for a function that compares two components and returns a list of component differences.
     * @param comp1 First component to compare (as std::any).
     * @param comp2 Second component to compare (as std::any).
     * @return A vector of component_info_t representing differences between the two components.
     */
    typedef std::function<std::vector<component_info_t>(const std::any &, const std::any &)> comparer_t;

    /**
     * @brief A tuple grouping the component management tools (destroyer, setter, comparer).
     */
    using component_tools_t = std::tuple<destroyer_t, setter_t, comparer_t>;

    /**
     * @brief A map that associates component types with their management tools and sparse arrays of component data.
     */
    using component_map_t = std::unordered_map<std::type_index, std::pair<std::any, component_tools_t>>;

    /**
     * @brief Default constructor for the Manager class.
     */
    Manager(void);

    /**
     * @brief Registers a component type in the ECS system.
     * @tparam Component The type of component to register.
     * @return A reference to a SparseArray containing the registered components.
     */
    template <class Component>
    SparseArray<Component> &registerComponent(void);

    /**
     * @brief Sets a specific component for an entity.
     * @tparam Component The type of the component being set.
     * @param from The entity to which the component is assigned.
     * @param component The component data.
     */
    template <class Component>
    void setComponent(entity::Entity from, const Component &component);

    /**
     * @brief Constructs and sets a component for an entity using parameters.
     * @tparam Component The type of component.
     * @tparam Params Parameter pack used to construct the component.
     * @param from The entity to which the component is assigned.
     * @param p Parameters forwarded to the component constructor.
     */
    template <typename Component, class... Params>
    void setComponent(entity::Entity from, Params &&...p);

    /**
     * @brief Sets a component for an entity using its type and a generic std::any object.
     * @param entity The entity to which the component is assigned.
     * @param type The type of the component (as std::type_index).
     * @param component The component data (as std::any).
     */
    void setComponent(entity::Entity entity, const std::type_index &type, const std::any &component);

    /**
     * @brief Sets a component based on provided component information.
     * @param infos The component information structure used to set the component.
     */
    void setComponent(const component_info_t &infos);

    /**
     * @brief Destroys a specific component of an entity.
     * @tparam Component The type of component to destroy.
     * @param from The entity whose component is to be destroyed.
     */
    template <class Component>
    void destroyComponent(entity::Entity from);

    /**
     * @brief Destroys all components associated with an entity.
     * @param from The entity whose components are to be destroyed.
     */
    void destroyComponents(entity::Entity from);

    /**
     * @brief Retrieves the sparse array of a specific type of component.
     * @tparam Component The type of component to retrieve.
     * @return A reference to the sparse array containing the components.
     */
    template <class Component>
    SparseArray<Component> &getComponents(void);

    /**
     * @brief Retrieves the sparse array of a specific type of component (const version).
     * @tparam Component The type of component to retrieve.
     * @return A const reference to the sparse array containing the components.
     */
    template <class Component>
    const SparseArray<Component> &getComponents(void) const;

    /**
     * @brief Retrieves the full component map.
     * @return A const reference to the component map.
     */
    const component_map_t &getComponentMap(void) const;

    /**
     * @brief Compares two sparse arrays of components and returns the differences.
     * @tparam Component The type of components to compare.
     * @param sparse1 The first sparse array of components.
     * @param sparse2 The second sparse array of components.
     * @return A vector of component_info_t representing the differences between the two sparse arrays.
     */
    template <class Component>
    std::vector<component_info_t> deltaDiffSparse(const SparseArray<Component> &sparse1,
                                                  const SparseArray<Component> &sparse2) const;

private:
    /**
     * @brief Stores the map of component types to their associated sparse arrays and management tools.
     */
    component_map_t m_componentMap;
};

/**
 * @brief Compares two component maps and returns the differences.
 * @param map1 The first component map.
 * @param map2 The second component map.
 * @return A vector of component_info_t of the components that changed between map1 and map2.
 */
std::vector<component_info_t> deltaDiff(const Manager::component_map_t &map1, const Manager::component_map_t &map2);
} // namespace ecs::component

#include "Manager.inl"
