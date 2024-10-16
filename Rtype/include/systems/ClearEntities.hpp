/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** ClearEntities.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "components/Bullet.hpp"
#include "components/Monster.hpp"

namespace rtype::system {
class ClearEntities
    : public gengine::System<ClearEntities, gengine::component::Transform2D, component::Bullet, component::Monster> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
    void clearBullets(void);
    void clearMonsters(void);
};
} // namespace rtype::system
