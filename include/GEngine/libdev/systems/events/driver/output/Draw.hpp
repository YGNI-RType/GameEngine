/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Draw.hpp
*/

#pragma once

#include "GEngine/libdev/Entity.hpp"
#include "GEngine/libdev/System.hpp"

namespace gengine::system::event {
class BeginDraw : public Event {
public:
    Color clear;
    BeginDraw(Color &&clear)
        : clear(clear) {
    }
    BeginDraw(Color &clear)
        : clear(clear) {
    }
};
class Draw : public Event {
public:
    Entity entity;
    Draw(Entity &&entity)
        : entity(entity) {
    }
    Draw(Entity entity)
        : entity(entity) {
    }
};
class EndDraw : public Event {};
} // namespace gengine::system::event
