/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** ClearBullets
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "components/Bullet.hpp"

namespace rtype::system {
class ClearBullets : public gengine::System<ClearBullets, gengine::component::Transform2D,
                                            gengine::component::driver::output::Animation, component::Bullet> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
    // void clearFires(void);
    void clearBullets(void);
};
} // namespace rtype::system
