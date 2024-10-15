/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Event
** ════════════════════════════════════════════════════════════════════════════
**  File        : Collision.hpp
**  Create at   : 2024-10-15 05:16
**  Author      : AUTHOR
**  Description : This event is natively published by the basic collision system
                    of libdev to indicate a collision between two entities.
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "GEngine/libdev/Entity.hpp"
#include "GEngine/libdev/System.hpp"

namespace gengine::system::event {
struct Collsion : public Event {
    Entity entity1;
    Entity entity2;
    Collsion(const Entity &entity1, const Entity entity2)
        : entity1(entity1)
        , entity2(entity2) {
    }
};
} // namespace gengine::system::event
