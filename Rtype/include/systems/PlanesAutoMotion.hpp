/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** PlanesAutoMotion.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"

#include "components/Plane.hpp"

namespace rtype::system {
class PlanesAutoMotion : public gengine::System<PlanesAutoMotion, gengine::component::Velocity2D, component::Plane> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
};
} // namespace rtype::system
