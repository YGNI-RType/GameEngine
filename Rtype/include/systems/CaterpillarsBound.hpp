/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** CaterpillarsBound.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "components/Caterpillar.hpp"

namespace rtype::system {
class CaterpillarsBound
    : public gengine::System<CaterpillarsBound, gengine::component::Velocity2D, gengine::component::Transform2D,
                             gengine::component::driver::output::Sprite, component::Caterpillar> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
};
} // namespace rtype::system
