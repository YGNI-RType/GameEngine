/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Iterator.hpp
*/

#pragma once

#include <tuple>
#include <variant>

#include "ecs/component/SparseArray.hpp"

namespace ecs::component {
/**
 * @brief A utility class that "zips" together multiple SparseArray instances for iteration.
 *
 * The Zipper allows simultaneous iteration over multiple SparseArray objects, ensuring that
 * only entities present in all the arrays are accessed. This can be useful for systems
 * that need to process multiple components for the same entity.
 *
 * @tparam Element Variadic template that represents the component types being zipped.
 */
template <class... Element>
class Zipper {
private:
    /**
     * @brief An iterator for the Zipper class.
     *
     * This iterator traverses multiple SparseArray instances in parallel, yielding
     * entities and their associated components when they exist in all arrays.
     */
    class Iterator {
    public:
        /**
         * @brief Type alias for the dense iterator of a SparseArray for a given Component.
         *
         * @tparam Component The type of component.
         */
        template <class Component>
        using iterator_t = typename SparseArray<Component>::dense_iterator;

        /**
         * @brief Constructs an Iterator for the provided SparseArray tuple.
         *
         * @param tuple A tuple of references to SparseArray instances to iterate over.
         */
        Iterator(std::tuple<SparseArray<Element> &...> &tuple);

        /**
         * @brief Constructs an end iterator for the provided SparseArray tuple.
         *
         * @param tuple A tuple of references to SparseArray instances to iterate over.
         * @param end A boolean indicating whether this is the end iterator.
         */
        Iterator(std::tuple<SparseArray<Element> &...> &tuple, bool end);

        /**
         * @brief Increments the iterator to the next valid entity and component set.
         *
         * @return A reference to the updated Iterator.
         */
        Iterator operator++(void);

        /**
         * @brief Compares two iterators for equality.
         *
         * @param other The other iterator to compare with.
         * @return True if both iterators are equal, false otherwise.
         */
        bool operator==(const Iterator &other) const;

        /**
         * @brief Compares two iterators for inequality.
         *
         * @param other The other iterator to compare with.
         * @return True if both iterators are not equal, false otherwise.
         */
        bool operator!=(const Iterator &other) const;

        /**
         * @brief Dereferences the iterator to access the current entity and its components.
         *
         * @return A tuple containing the current entity and its associated components.
         */
        std::tuple<const entity::Entity, Element &...> operator*(void);

    private:
        /// A tuple of references to the SparseArray instances being iterated over.
        std::tuple<SparseArray<Element> &...> &m_arrays;

        /// The iterator to the smallest dense array of the SparseArrays. Assigned dynamically at runtime.
        std::variant<iterator_t<Element>...> m_smallestIt;

        /// The current index being iterated over.
        std::size_t m_idx = 0;

        /// The size of the smallest dense array of the SparseArray instance being iterated.
        std::size_t m_max;

        /**
         * @brief Checks if all arrays contain the same entity at the current index.
         *
         * @tparam I A parameter pack representing the indices of the arrays.
         * @param entity The entity to check for existence in all arrays.
         * @return True if the entity exists in all arrays, false otherwise.
         */
        template <std::size_t... I>
        bool m_hasAllElement(entity::Entity entity, std::index_sequence<I...>) const;

        /**
         * @brief Retrieves the entity and components from all arrays at the current index.
         *
         * @tparam I A parameter pack representing the indices of the arrays.
         * @param entity The entity to retrieve components for.
         * @return A tuple containing the entity and its associated components.
         */
        template <std::size_t... I>
        std::tuple<const entity::Entity, Element &...> m_getAllElement(entity::Entity entity,
                                                                       std::index_sequence<I...>) const;

        /**
         * @brief Sets the smallest iterator among the arrays, starting from the given index.
         *
         * @tparam F The first array index.
         * @tparam I The remaining array indices.
         * @param end A boolean indicating whether to set the end iterator.
         */
        template <std::size_t F, std::size_t... I>
        void setSmallest(std::index_sequence<F, I...>, bool end = false);
    };

public:
    /**
     * @brief Constructs a Zipper for multiple SparseArray instances.
     *
     * @param elem The SparseArray instances to zip together.
     */
    Zipper(SparseArray<Element> &...elem);

    /**
     * @brief Returns an iterator to the beginning of the zipped SparseArray instances.
     *
     * @return An iterator to the first valid entity and component set.
     */
    Iterator begin(void);

    /**
     * @brief Returns an iterator to the end of the zipped SparseArray instances.
     *
     * @return An iterator to the end.
     */
    Iterator end(void);

private:
    /// A tuple of references to the SparseArray instances being zipped together.
    std::tuple<SparseArray<Element> &...> m_elements;
};
} // namespace ecs::component

#include "Iterator.inl"
