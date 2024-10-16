/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** ECS.cpp
*/

#include "ecs/ECS.hpp"

using namespace ecs;

ECS::ECS()
    : system::Manager(*this) {
}

void ECS::killEntity(entity::Entity entity) {
    unsetComponents(entity);
    destroyEntity(entity);
}

template <typename T>
void publishEvent(T &event) {
    publishEvent<T>(event);
}

template <typename T>
void publishEvent(T &&event) {
    publishEvent<T>(event);
}
