/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Manager.cpp
*/

#include "ecs/system/Manager.hpp"

namespace ecs::system {
void Manager::executeEvent(void) {
    m_eventBus.execute();
}

bool Manager::hasEvent(void) {
    return !m_eventBus.isEmpty();
}
} // namespace ecs::system