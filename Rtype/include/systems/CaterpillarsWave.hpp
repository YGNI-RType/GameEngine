/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** CaterpillarsWave.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/HitBoxs.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "components/Caterpillar.hpp"
#include "components/Monster.hpp"
#include "components/Score.hpp"

namespace rtype::system {
class CaterpillarsWave
    : public gengine::System<CaterpillarsWave, gengine::component::HitBoxSquare2D, gengine::component::Transform2D,
                             gengine::component::Velocity2D, gengine::component::driver::output::Drawable,
                             gengine::component::driver::output::Sprite, component::Monster, component::Caterpillar> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
    void spawnWave(void);
};
} // namespace rtype::system
