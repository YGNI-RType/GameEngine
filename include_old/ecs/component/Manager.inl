/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Manager.inl
*/

#pragma once

namespace ecs::component {
template <class T> SparseArray<T> &Manager::registerComponent() {
    static_assert(std::is_base_of<ecs::component::IsComponent, T>::value, "T must inherit from component::Base");
    auto res = m_componentArrays.emplace(
        std::type_index(typeid(T)),
        std::make_pair(SparseArray<T>(), [this](entity::Entity entity) { destroyComponent<T>(entity); }));
    return std::any_cast<SparseArray<T> &>(res.first->second.first);
}

template <class T> void Manager::setComponent(entity::Entity entity, const T &component) {
    getComponents<T>().insert(entity, component);
}

template <class T> void Manager::destroyComponent(entity::Entity entity) { getComponents<T>().erase(entity); }

template <typename T, class... Params> void Manager::setComponent(entity::Entity entity, Params &&...p) {
    getComponents<T>().emplace(entity, T(std::forward<Params>(p)...));
}

template <class T> SparseArray<T> &Manager::getComponents() {
    auto it = m_componentArrays.find(std::type_index(typeid(T)));
    if (it == m_componentArrays.end())
        THROW_ERROR("The component " + std::string(READABLE_TYPE_NAME(T)) + " does not exist in the Manager");
    return std::any_cast<SparseArray<T> &>(it->second.first);
}

template <class T> const SparseArray<T> &Manager::getComponents() const {
    auto it = m_componentArrays.find(std::type_index(typeid(T)));
    if (it == m_componentArrays.end())
        THROW_ERROR("The component " + std::string(READABLE_TYPE_NAME(T)) + " does not exist in the Manager");
    return std::any_cast<const SparseArray<T> &>(it->second);
}
} // namespace ecs::component
