/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** PlanesWave.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/HitBoxs.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "components/Monster.hpp"
#include "components/Plane.hpp"
#include "components/Score.hpp"

namespace rtype::system {
class PlanesWave
    : public gengine::System<PlanesWave, gengine::component::HitBoxSquare2D, gengine::component::Transform2D,
                             gengine::component::Velocity2D, gengine::component::driver::output::Animation,
                             gengine::component::driver::output::Drawable, gengine::component::driver::output::Sprite,
                             component::Monster, component::Plane> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
    void spawnWave(void);
};
} // namespace rtype::system
