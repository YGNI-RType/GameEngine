/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MonstersAutoMotion.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"

#include "components/Monster.hpp"

namespace rtype::system {
class MonstersAutoMotion : public gengine::System<MonstersAutoMotion, gengine::component::Velocity2D,
                                                  component::Monster, gengine::component::driver::output::Animation> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
};
} // namespace rtype::system
