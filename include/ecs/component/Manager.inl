/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Manager.inl
*/

#pragma once

namespace ecs::component {
template <class T>
ComponentTools Manager::registerTools(void) {
    return ComponentTools(
        m_componentMap.size() - 1, sizeof(T), [this](entity::Entity entity) { unsetComponent<T>(entity); },
        [this](entity::Entity entity, const std::any &any) { setComponent<T>(entity, std::any_cast<const T &>(any)); },
        [this](const std::any any1, const std::any &any2) {
            return deltaDiffSparse<T>(std::any_cast<const SparseArray<T>>(any1),
                                      std::any_cast<const SparseArray<T> &>(any2));
        },
        [this](const std::any &any) { return &std::any_cast<const T &>(any); },
        [this](const void *ptr) { return *static_cast<const T *>(ptr); });
}

template <class T>
SparseArray<T> &Manager::registerComponent(void) {
    static_assert(std::is_base_of<ecs::component::IsComponent<T>, T>::value, "T must inherit from component::Base");
    auto res = m_componentMap.emplace(std::type_index(typeid(T)), SparseArray<T>());
    m_componentToolsMap.emplace(res.first->first, registerTools<T>());
    return std::any_cast<SparseArray<T> &>(res.first->second);
}

template <class T>
void Manager::setComponent(entity::Entity entity, const T &component) {
    getComponents<T>().insert(entity, component);
}

template <typename T, class... Params>
void Manager::setComponent(entity::Entity entity, Params &&...p) {
    getComponents<T>().emplace(entity, T(std::forward<Params>(p)...));
}

template <class T>
void Manager::unsetComponent(entity::Entity entity) {
    getComponents<T>().erase(entity);
}

template <class T>
SparseArray<T> &Manager::getComponents(void) {
    auto it = m_componentMap.find(std::type_index(typeid(T)));
    if (it == m_componentMap.end())
        THROW_ERROR("The component " + std::string(READABLE_TYPE_NAME(T)) + " does not exist in the Manager");
    return std::any_cast<SparseArray<T> &>(it->second);
}

template <class T>
const SparseArray<T> &Manager::getComponents(void) const {
    auto it = m_componentMap.find(std::type_index(typeid(T)));
    if (it == m_componentMap.end())
        THROW_ERROR("The component " + std::string(READABLE_TYPE_NAME(T)) + " does not exist in the Manager");
    return std::any_cast<const SparseArray<T> &>(it->second);
}

template <class Component>
std::vector<component_info_t> Manager::deltaDiffSparse(const SparseArray<Component> &sparse1,
                                                       const SparseArray<Component> &sparse2) const {
    std::vector<component_info_t> diff;
    const std::type_index &type = m_componentMap.find(typeid(Component))->first;

    for (auto it = sparse1.cbegin(), end = sparse1.cend(); it != end; it++) {
        auto &[entity, component] = *it;
        if (!sparse2.contains(entity) || component != sparse2.get(entity))
            diff.emplace_back(entity, type, true, component);
    }
    for (auto it = sparse2.cbegin(), end = sparse2.cend(); it != end; it++) {
        auto &[entity, component] = *it;
        if (!sparse1.contains(entity))
            diff.emplace_back(entity, type, false, std::any());
    }
    return diff;
}
} // namespace ecs::component
