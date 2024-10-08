/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** component::Manager.cpp
*/

#include "ecs/component/Manager.hpp"

using namespace ecs;

component::Manager::Manager(void)
    : m_componentMap()
    , m_componentToolsMap() {
}

void component::Manager::setComponent(entity::Entity entity, const std::type_index &type, const std::any &component) {
    auto it = m_componentToolsMap.find(type);
    if (it == m_componentToolsMap.end())
        THROW_ERROR("The component " + std::string(type.name()) + " does not exist in the Manager");
    auto &[d, setter, c, i] = it->second;
    setter(entity, component);
}

void component::Manager::setComponent(const component_info_t &infos) {
    auto &[entity, type, component] = infos;
    setComponent(entity, type, component);
}

void component::Manager::destroyComponents(entity::Entity entity) {
    for (auto it : m_componentToolsMap) {
        auto &[destroyer, s, c, i] = it.second;
        destroyer(entity);
    }
}

const component::Manager::component_map_t &component::Manager::getComponentMap(void) const {
    return m_componentMap;
}

const component::Manager::component_tools_map_t &component::Manager::getComponentToolsMap(void) const {
    return m_componentToolsMap;
}

std::vector<component::component_info_t> component::deltaDiff(const component::Manager::component_map_t &map1,
                                                              const component::Manager::component_tools_map_t &tools,
                                                              const component::Manager::component_map_t &map2) {
    std::vector<component::component_info_t> diff;

    for (auto &[type, component] : map1) {
        if (!map2.contains(type))
            THROW_ERROR("the 2 world do not contain the same component"); // big error
        auto &[d, s, comparer, i] = tools.find(type)->second;
        for (auto [e, t, c] : comparer(component, map2.find(type)->second))
            diff.emplace_back(e, t, c);
    }
    return diff;
}
