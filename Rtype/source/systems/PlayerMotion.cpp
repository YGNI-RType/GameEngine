/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** PlayerMotion.cpp
*/

#include "systems/PlayerMotion.hpp"

#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"

#include "GEngine/libdev/Component.hpp" // gengine::Zip

#include <random>

namespace rtype::system {
void PlayerMotion::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&PlayerMotion::onGameLoop);
    subscribeToEvent<gengine::interface::network::event::RemoteEvent<event::Movement>>(&PlayerMotion::movePlayer);
}

void PlayerMotion::onGameLoop(gengine::system::event::GameLoop &e) {
    auto &velocities = getComponents<gengine::component::Velocity2D>();
    auto &transforms = getComponents<gengine::component::Transform2D>();
    auto &players = getComponents<component::Player>();

    for (auto [entity, player, velocity, transform] : gengine::Zip(players, velocities, transforms)) {
        if (transform.pos.x < 0) {
            transform.pos.x = 0;
            velocity.x = 0;
        } else if (transform.pos.x > 1280 - 33 * 3) {
            transform.pos.x = 1280 - 33 * 3;
            velocity.x = 0;
        }

        if (transform.pos.y < 0) {
            transform.pos.y = 0;
            velocity.y = 0;
        } else if (transform.pos.y > 720 - 17 * 3) {
            transform.pos.y = 720 - 17 * 3;
            velocity.y = 0;
        }
    }
}

void PlayerMotion::movePlayer(gengine::interface::network::event::RemoteEvent<event::Movement> &e) {
    auto &velocities = getComponents<gengine::component::Velocity2D>();
    auto &players = getComponents<component::Player>();
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();

    for (auto [entity, remote, player, velocity] : gengine::Zip(remotes, players, velocities)) {
        if (remote != e.remote) // check if its the same remote (zip)
            continue;
        switch (e->state) {
        case event::Movement::LEFT:
            velocity = {-player.speed, 0};
            break;
        case event::Movement::RIGHT:
            velocity = {player.speed, 0};
            break;
        case event::Movement::UP:
            velocity = {0, -player.speed};
            break;
        case event::Movement::DOWN:
            velocity = {0, player.speed};
            break;
        case event::Movement::UP_RIGHT:
            velocity = {player.speed, -player.speed};
            break;
        case event::Movement::UP_LEFT:
            velocity = {-player.speed, -player.speed};
            break;
        case event::Movement::DOWN_RIGHT:
            velocity = {player.speed, player.speed};
            break;
        case event::Movement::DOWN_LEFT:
            velocity = {-player.speed, player.speed};
            break;
        case event::Movement::STANDING:
            velocity = {0, 0};
            break;
        }
    }
}
} // namespace rtype::system
