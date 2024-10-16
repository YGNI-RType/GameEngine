/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Bus.cpp
*/

#include "ecs/system/event/Bus.hpp"

namespace ecs::system::event {
void Bus::execute(void) {
    m_toExecute.front()();
    m_toExecute.pop();
}

bool Bus::isEmpty(void) {
    return m_toExecute.empty();
}
} // namespace ecs::system::event
