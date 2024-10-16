/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** DestroyOnCollision.hpp
*/

#pragma once

#include "ecs/entity/Entity.hpp"

#include "GEngine/interface/components/RemoteDriver.hpp"
#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Text.hpp"
#include "GEngine/libdev/systems/events/game/Collision.hpp"

#include "GEngine/libdev/components/Transforms.hpp"
#include "components/Bullet.hpp"
#include "components/Life.hpp"
#include "components/Monster.hpp"
#include "components/Player.hpp"
#include "components/Score.hpp"

#include "ecs/entity/Entity.hpp"

namespace rtype::system {
class DestroyOnCollision
    : public gengine::System<DestroyOnCollision, component::Bullet, component::Monster, component::Life,
                             component::Player, gengine::interface::component::RemoteDriver,
                             gengine::component::Transform2D, component::Score,
                             gengine::component::driver::output::Drawable, gengine::component::driver::output::Text> {
public:
    void init(void) override;
    void destroyMonster(gengine::system::event::Collsion &);
    void destroyPlayer(gengine::system::event::Collsion &);

private:
    void claimScore(ecs::entity::Entity entity, const char *forPlayerUuid);
    void playerHit(ecs::entity::Entity, component::Player &, gengine::component::Transform2D &);
    void removeLife(void);
};
} // namespace rtype::system
