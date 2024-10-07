/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Iterator.inl
*/

#pragma once

#include <tuple>
#include <variant>

namespace ecs::component {
template <class... Element>
Zipper<Element...>::Iterator::Iterator(std::tuple<SparseArray<Element> &...> &tuple)
    : m_arrays(tuple) {
    setSmallest(std::index_sequence_for<Element...>());
};
template <class... Element>
Zipper<Element...>::Iterator::Iterator(std::tuple<SparseArray<Element> &...> &tuple, bool end)
    : m_arrays(tuple) {
    setSmallest(std::index_sequence_for<Element...>(), true);
};

template <class... Element>
typename Zipper<Element...>::Iterator Zipper<Element...>::Iterator::operator++(void) {
    return std::visit(
        [this](auto &&it) -> Iterator {
            do { // TODO might segv but Undefined behavior like vector
                ++m_idx;
                ++it;
            } while (m_idx < m_max && !m_hasAllElement(it->first, std::index_sequence_for<Element...>()));
            return *this;
        },
        m_smallestIt);
}

template <class... Element>
bool Zipper<Element...>::Iterator::operator==(const Zipper<Element...>::Iterator &other) const {
    return std::visit(
        [this](auto &&it, auto &&other) -> bool {
            if constexpr (std::is_same_v<std::decay_t<decltype(it)>, std::decay_t<decltype(other)>>)
                return it == other;
            return false;
        },
        m_smallestIt, other.m_smallestIt);
}
template <class... Element>
bool Zipper<Element...>::Iterator::operator!=(const Zipper<Element...>::Iterator &other) const {
    return !(this->operator==(other));
}

template <class... Element>
std::tuple<const entity::Entity, Element &...> Zipper<Element...>::Iterator::operator*(void) {
    return std::visit([this](auto &&it) { return m_getAllElement(it->first, std::index_sequence_for<Element...>()); },
                      m_smallestIt);
}

template <class... Element>
template <std::size_t... I>
bool Zipper<Element...>::Iterator::m_hasAllElement(entity::Entity entity, std::index_sequence<I...>) const {
    return (std::get<I>(m_arrays).contains(entity) && ...);
}

template <class... Element>
template <std::size_t... I>
std::tuple<const entity::Entity, Element &...>
Zipper<Element...>::Iterator::m_getAllElement(entity::Entity entity, std::index_sequence<I...>) const {
    return std::tie(entity, std::get<I>(m_arrays).get(entity)...);
}

template <class... Element>
template <std::size_t F, std::size_t... I>
void Zipper<Element...>::Iterator::setSmallest(std::index_sequence<F, I...>, bool end) {
    m_max = std::get<F>(m_arrays).size();
    m_smallestIt = !end ? std::get<F>(m_arrays).begin() : std::get<F>(m_arrays).end();

    auto updateSmallest = [&](auto &container) {
        auto size = container.size();
        if (size < m_max) {
            m_max = size;
            m_smallestIt = !end ? container.begin() : container.end();
        }
    };

    (updateSmallest(std::get<I>(m_arrays)), ...);

    std::visit(
        [&](auto &&it) {
            while (!end && m_idx < m_max && !m_hasAllElement(it->first, std::index_sequence_for<Element...>())) {
                ++m_idx;
                ++it;
            }
        },
        m_smallestIt);
}

template <class... Element>
Zipper<Element...>::Zipper(SparseArray<Element> &...elem)
    : m_elements(elem...) {
}

template <class... Element>
typename Zipper<Element...>::Iterator Zipper<Element...>::begin(void) {
    return Iterator(m_elements);
};
template <class... Element>
typename Zipper<Element...>::Iterator Zipper<Element...>::end(void) {
    return Iterator(m_elements, true);
}
} // namespace ecs::component
