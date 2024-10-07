/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** component::Manager.cpp
*/

#include "ecs/component/Manager.hpp"

using namespace ecs;

component::Manager::Manager() {
}

void component::Manager::setComponent(entity::Entity entity, const std::type_index &type, const std::any &component) {
    auto it = m_componentMap.find(type);
    if (it == m_componentMap.end())
        THROW_ERROR("The component " + std::string(type.name()) + " does not exist in the Manager");
    auto &[d, setter, c] = it->second.second;
    setter(entity, component);
}

void component::Manager::setComponent(const component_info_t &infos) {
    auto &[entity, type, component] = infos;
    setComponent(entity, type, component);
}

void component::Manager::destroyComponents(entity::Entity entity) {
    for (auto it : m_componentMap) {
        auto &[destroyer, s, c] = it.second.second;
        destroyer(entity);
    }
}

const component::Manager::component_map_t &component::Manager::getComponentMap(void) const {
    return m_componentMap;
}

std::vector<component::component_info_t> component::deltaDiff(const component::Manager::component_map_t &map1,
                                                              const component::Manager::component_map_t &map2) {
    std::vector<component::component_info_t> diff;

    for (auto &[type, pair] : map1) {
        if (!map2.contains(type))
            THROW_ERROR("the 2 world do not contain the same component");
        auto &[d, s, comparer] = pair.second;
        for (auto [e, t, c] : comparer(pair.first, map2.find(type)->second.first))
            diff.emplace_back(e, t, c);
    }
    return diff;
}
