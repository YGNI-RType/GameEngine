/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MainLoop.hpp
*/

#pragma once

#include "GEngine/libdev/Entity.hpp"
#include "GEngine/libdev/System.hpp"

namespace gengine::system::event {
struct Collsion : public Event {
    Entity entity1;
    Entity entity2;
    Collsion(const Entity &entity1, const Entity entity2) : entity1(entity1), entity2(entity2) {}
};
} // namespace gengine::system::event
