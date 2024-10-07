/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** entity::Manager.cpp
*/

#include "ecs/entity/Manager.hpp"

using namespace ecs;

entity::Manager::Manager()
    : m_size(0) {
}

entity::Entity entity::Manager::createEntity() {
    entity::Entity entity;
    if (!m_available.empty()) {
        entity = m_available.front();
        m_available.pop();
    } else
        entity = m_size++;
    return entity;
}

void entity::Manager::destroyEntity(entity::Entity dead) {
    m_available.push(dead);
}
