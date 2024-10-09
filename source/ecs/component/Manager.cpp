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
    auto &setter = it->second.setter();
    setter(entity, component);
}

void component::Manager::setComponent(const component_info_t &infos) {
    auto &[entity, type, component] = infos;
    setComponent(entity, type, component);
}

void component::Manager::destroyComponents(entity::Entity entity) {
    for (auto it : m_componentToolsMap) {
        auto &destroyer = it.second.destroyer();
        destroyer(entity);
    }
}

const component::Manager::component_map_t &component::Manager::getComponentMap(void) const {
    return m_componentMap;
}

component::ComponentTools::component_id_t component::Manager::getComponentId(const std::type_index &type) const {
    return m_componentToolsMap.find(type)->second.id();
}
const std::type_index &component::Manager::getTypeindex(ComponentTools::component_id_t id) const { //TODO better opti
    for (auto &[type, tool] : m_componentToolsMap) {
        if (tool.id() == id)
            return type;
    }
    THROW_ERROR("component id does not exist");
}
component::ComponentTools::component_size_t component::Manager::getComponentSize(const std::type_index &type) const {
    return m_componentToolsMap.find(type)->second.size();
}
std::vector<component::component_info_t>
component::Manager::compareComponents(const std::type_index &type, const std::any &any1, const std::any &any2) const {
    return m_componentToolsMap.find(type)->second.comparer()(any1, any2);
}
const void *component::Manager::toVoid(const std::type_index &type, const std::any &any) const {
    return m_componentToolsMap.find(type)->second.voider()(any);
}
const std::any component::Manager::toAny(const std::type_index &type, const void *component) const {
    return m_componentToolsMap.find(type)->second.anyer()(component);
}

// const component::Manager::component_tools_map_t &component::Manager::getComponentToolsMap(void) const {
//     return m_componentToolsMap;
// }

// std::vector<component::component_info_t> component::deltaDiff(const component::Manager::component_map_t &map1,
//                                                               const component::Manager::component_tools_map_t &tools,
//                                                               const component::Manager::component_map_t &map2) {
//     std::vector<component::component_info_t> diff;

//     for (auto &[type, component] : map1) {
//         if (!map2.contains(type))
//             THROW_ERROR("the 2 world do not contain the same component"); // big error
//         auto &comparer = tools.find(type)->second.comparer();
//         for (auto [e, t, c] : comparer(component, map2.find(type)->second))
//             diff.emplace_back(e, t, c);
//     }
//     return diff;
// }
