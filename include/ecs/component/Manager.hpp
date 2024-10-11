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
 * @class ComponentTools
 * @brief Provides utility tools for handling components in an ECS (Entity-Component System).
 *
 * This class encapsulates various functions that manage the lifecycle of components,
 * such as destroying, setting, comparing, and converting components. It supports
 * multiple component types through the use of `std::any`, allowing generic
 * management of components in the ECS system.
 */
class ComponentTools {
public:
    typedef uint16_t component_id_t;   ///< Unique identifier type for a component. Needed because std::type_index is
                                       ///< unreliable between computers.
    typedef uint16_t component_size_t; ///< Size type for a component.

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
     * @return A vector of `component_info_t` representing differences between the two components.
     */
    typedef std::function<std::vector<component_info_t>(const std::any &, const std::any &)> comparer_t;

    /**
     * @brief Type alias for a function that retrieves a raw pointer to the data held in a `std::any` object.
     * @param component The component data as `std::any`.
     * @return A const pointer to the underlying data.
     */
    typedef std::function<const void *(const std::any &)> voider_t;

    /**
     * @brief Type alias for a function that wraps a raw pointer into a `std::any` object.
     * @param component Pointer to the raw data of the component.
     * @return The component data as a `std::any` object.
     */
    typedef std::function<std::any(const void *)> anyer_t;

    /**
     * @brief Constructs a ComponentTools object.
     * @param id The unique ID of the component.
     * @param size The size of the component in bytes.
     * @param destroyer Function responsible for destroying the component.
     * @param setter Function responsible for setting the component.
     * @param comparer Function responsible for comparing two components.
     * @param voider Function responsible for retrieving the raw pointer of a component.
     * @param anyer Function responsible for wrapping raw pointers in `std::any`.
     */
    ComponentTools(component_id_t id, component_size_t size, destroyer_t destroyer, setter_t setter,
                   comparer_t comparer, voider_t voider, anyer_t anyer);

    /// @return The unique ID of the component.
    const component_id_t &id(void) const;

    /// @return The size of the component.
    const component_size_t &size(void) const;

    /// @return The destroyer function for the component.
    const destroyer_t &destroyer(void);

    /// @return The setter function for the component.
    const setter_t &setter(void);

    /// @return The comparer function for comparing two components.
    const comparer_t &comparer(void) const;

    /// @return The voider function that retrieves a raw pointer from a component.
    const voider_t &voider(void) const;

    /// @return The anyer function that wraps a raw pointer in `std::any`.
    const anyer_t &anyer(void) const;

private:
    component_id_t m_componentId; ///< The unique ID of the component.
    component_size_t m_size;      ///< The size of the component in bytes.

    destroyer_t m_destroyer; ///< Function responsible for destroying the component.
    setter_t m_setter;       ///< Function responsible for setting the component.
    comparer_t m_comparer;   ///< Function responsible for comparing two components.
    voider_t m_voider;       ///< Function to get a raw pointer from a component.
    anyer_t m_anyer;         ///< Function to wrap a raw pointer in `std::any`.
};

/**
 * @class Manager
 * @brief Manages the registration, setting, and destruction of components for entities in an ECS (Entity-Component
 * System).
 *
 * The Manager class handles a variety of component types by leveraging `std::any`.
 * It maintains mappings between component types and their corresponding management tools,
 * such as sparse arrays for storing component data, and provides functions for setting,
 * destroying, and comparing components.
 */
class Manager {
public:
    /**
     * @brief A map that associates component types with their management tools and sparse arrays of component data.
     * The key is the `std::type_index` representing the component type.
     */
    using component_map_t = std::unordered_map<std::type_index, std::any>;

    /**
     * @brief A map that associates component types with their corresponding `ComponentTools` instance.
     * This map helps manage lifecycle functions for each component type.
     */
    using component_tools_map_t = std::unordered_map<std::type_index, ComponentTools>;

    /// @brief Default constructor for the Manager class.
    Manager(void);

    /**
     * @brief Registers a component type in the ECS system.
     * @tparam Component The type of component to register.
     * @return A reference to a `SparseArray` containing the registered components.
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
     * @brief Sets a component for an entity using its type and a generic `std::any` object.
     * @param entity The entity to which the component is assigned.
     * @param type The type of the component (as `std::type_index`).
     * @param component The component data (as `std::any`).
     */
    void setComponent(entity::Entity entity, const std::type_index &type, const std::any &component);

    /**
     * @brief Unset a specific component of an entity.
     * @tparam Component The type of component to unset.
     * @param from The entity whose component is to be unset.
     */
    template <class Component>
    void unsetComponent(entity::Entity from);

    /**
     * @brief Unset a specific component of an entity using its type.
     * @param from The entity whose component is to be unset.
     * @param type The type of the component (as `std::type_index`).
     */
    void unsetComponent(entity::Entity from, const std::type_index &type);

    /**
     * @brief Unset all components associated with an entity.
     * @param from The entity whose components are to be unset.
     */
    void unsetComponents(entity::Entity from);

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
     * @brief Retrieves the component ID for a given type.
     * @param type The type of the component (as `std::type_index`).
     * @return The unique ID of the component.
     */
    ComponentTools::component_id_t getComponentId(const std::type_index &type) const;

    /**
     * @brief Retrieves the type index for a given component ID.
     * @param id The ID of the component.
     * @return The `std::type_index` representing the component type.
     */
    const std::type_index &getTypeindex(ComponentTools::component_id_t id) const;

    /**
     * @brief Retrieves the size of a component type.
     * @param type The type of the component (as `std::type_index`).
     * @return The size of the component in bytes.
     */
    ComponentTools::component_size_t getComponentSize(const std::type_index &type) const;

    /**
     * @brief Compares two sparse arrays of components of a given type and returns the differences.
     *
     * The difference will be the new components or the ones that changed from the any2 to any1.
     * @param type The type of the components (as `std::type_index`).
     * @param any1 The first sparse array to compare (as `std::any`).
     * @param any2 The second sparse array to compare (as `std::any`).
     * @return A vector of `component_info_t` representing the differences between the two sparse array.
     */
    std::vector<component_info_t> compareComponents(const std::type_index &type, const std::any &any1,
                                                    const std::any &any2) const;

    /**
     * @brief Converts a component into a raw pointer.
     * @param type The type of the component (as `std::type_index`).
     * @param any The component data (as `std::any`).
     * @return A raw pointer to the component's underlying data.
     */
    const void *toVoid(const std::type_index &type, const std::any &any) const;

    /**
     * @brief Converts a raw pointer to a component back into a `std::any` object.
     * @param type The type of the component (as `std::type_index`).
     * @param component Pointer to the raw data of the component.
     * @return The component data as a `std::any`.
     */
    const std::any toAny(const std::type_index &type, const void *component) const;

private:
    component_map_t m_componentMap;            ///< Stores the map of component types to sparse arrays.
    component_tools_map_t m_componentToolsMap; ///< Stores the map of component types to their management tools.

    /**
     * @brief Registers the necessary tools for managing a component type.
     * @tparam T The component type to register.
     * @return A `ComponentTools` instance for managing the component.
     */
    template <class T>
    ComponentTools registerTools(void);

    /**
     * @brief Compares two sparse arrays of components and returns the differences.
     * @tparam Component The type of components to compare.
     * @param sparse1 The first sparse array of components.
     * @param sparse2 The second sparse array of components.
     * @return A vector of `component_info_t` representing the differences between the two sparse arrays.
     */
    template <class Component>
    std::vector<component_info_t> deltaDiffSparse(const SparseArray<Component> &sparse1,
                                                  const SparseArray<Component> &sparse2) const;
};
} // namespace ecs::component

#include "Manager.inl"
