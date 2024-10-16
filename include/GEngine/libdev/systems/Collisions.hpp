/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : Collisions.hpp
**  Create at   : 2024-10-15 05:04
**  Author      : AUTHOR
**  Description : This system dedicated to the GameEngine, allows to basically
                    calculate collisions between all game entities and publish
                    an event in reaction.
** ═══════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/HitBoxs.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "GEngine/libdev/systems/events/game/Collision.hpp"

namespace gengine::system {
class Collision2D
    : public System<Collision2D, component::Transform2D, component::HitBoxSquare2D, component::HitBoxCircle2D> {
public:
    void init(void) override;
    void onGameLoop(event::GameLoop &);
};

class Collision3D
    : public System<Collision3D, component::Transform3D, component::HitBoxSquare3D, component::HitBoxCircle3D> {
public:
    void init(void) override;
    void onGameLoop(event::GameLoop &);
};
} // namespace gengine::system