/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** component::Manager.cpp
*/

#include "ecs/component/Manager.hpp"

using namespace ecs;

component::Manager::Manager() {}

void component::Manager::destroyComponents(entity::Entity entity) {
    for (auto &[_, pair] : m_componentArrays)
        pair.second(entity);
}