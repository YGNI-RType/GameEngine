/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** SparseArray.inl
*/

#pragma once

namespace ecs::component {
template <class Component>
void SparseArray<Component>::reserve(entity::Entity capacity) {
    m_sparse.resize(capacity, invalid_index);
}

template <class Component>
void SparseArray<Component>::insert(entity::Entity entity, const Component &component) {
    if (entity >= m_sparse.size())
        reserve(entity + 1);

    if (m_sparse[entity] == invalid_index) {
        m_sparse[entity] = m_dense.size();
        m_dense.emplace_back(entity, component);
    } else {
        m_dense[m_sparse[entity]].second = component;
    }
}

template <class Component>
template <typename... Params>
void SparseArray<Component>::emplace(entity::Entity entity, Params &&...p) {
    if (entity >= m_sparse.size())
        reserve(entity + 1);

    if (m_sparse[entity] == invalid_index) {
        m_sparse[entity] = m_dense.size();
        m_dense.emplace_back(entity, Component(std::forward<Params>(p)...));
    } else {
        m_dense[m_sparse[entity]].second = Component(std::forward<Params>(p)...);
    }
}

template <class Component>
void component::SparseArray<Component>::erase(entity::Entity entity) {
    if (entity >= m_sparse.size() || m_sparse[entity] == invalid_index)
        return;

    entity::Entity denseIndex = m_sparse[entity];
    entity::Entity lastDenseIndex = m_dense.size() - 1;
    if (denseIndex != lastDenseIndex) {
        std::swap(m_dense[denseIndex], m_dense[lastDenseIndex]);
        m_sparse[m_dense[denseIndex].first] = denseIndex;
    }
    m_dense.pop_back();
    m_sparse[entity] = invalid_index;
}

template <class Component>
bool SparseArray<Component>::contains(entity::Entity entity) const {
    return entity < m_sparse.size() && m_sparse[entity] != invalid_index;
}

template <class Component>
Component &SparseArray<Component>::get(entity::Entity entity) {
    return m_dense[m_sparse[entity]].second;
}

template <class Component>
const Component &SparseArray<Component>::get(entity::Entity entity) const {
    return m_dense[m_sparse[entity]].second;
}

template <class Component>
std::size_t SparseArray<Component>::size() const {
    return m_dense.size();
}

template <class Component>
std::size_t SparseArray<Component>::reserved() const {
    return m_sparse.size();
}

template <class Component>
typename SparseArray<Component>::dense_iterator SparseArray<Component>::begin() {
    return m_dense.begin();
}
template <class Component>
typename SparseArray<Component>::dense_iterator SparseArray<Component>::end() {
    return m_dense.end();
}
template <class Component>
typename SparseArray<Component>::dense_const_iterator SparseArray<Component>::cbegin() const {
    return m_dense.cbegin();
}
template <class Component>
typename SparseArray<Component>::dense_const_iterator SparseArray<Component>::cend() const {
    return m_dense.cend();
}
} // namespace ecs::component