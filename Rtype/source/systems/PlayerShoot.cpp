/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** PlayerShoot.cpp
*/

#include "systems/PlayerShoot.hpp"
#include "components/Bullet.hpp"

// Spawn entity
#include "GEngine/libdev/Component.hpp" // gengine::Zip
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/components/Velocities.hpp"

namespace rtype::system {
void PlayerShoot::init(void) {
    subscribeToEvent<gengine::system::event::driver::input::Key_B>(&PlayerShoot::shoot);
}

void PlayerShoot::shoot(gengine::system::event::driver::input::Key_B &e) {
    auto &players = getComponents<component::PlayerControl>();
    auto &transforms = getComponents<gengine::component::Transform2D>();

    for (auto [entity, player, transform] : gengine::Zip(players, transforms)) {
        // spawnEntity(component::Fire(),
        //             gengine::component::Transform2D({transform.pos.x + 93, transform.pos.y + 22}, {2, 2}, 0),
        //             gengine::component::driver::output::Sprite("r-typesheet1.gif", Rectangle{214, 85, 17, 12},
        //             WHITE), gengine::component::driver::output::Animation(2, 0, 0.05f, false),
        //             gengine::component::driver::output::Drawable(1));

        spawnEntity(component::Bullet(),
                    gengine::component::Transform2D({transform.pos.x + 93, transform.pos.y + 22}, {2, 2}, 0),
                    gengine::component::Velocity2D(1000 / 100, 0),
                    gengine::component::driver::output::Sprite("r-typesheet1.gif", Rectangle{248, 85, 17, 12}, WHITE),
                    gengine::component::driver::output::Drawable(1), gengine::component::HitBoxSquare2D(17, 12));
    }
}
} // namespace rtype::system
