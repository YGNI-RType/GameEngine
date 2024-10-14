/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile->fouquet
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
    subscribeToEvent<ClientEvent<gengine::system::event::driver::input::Key_Left>>(&PlayerMotion::movePlayerLeft);
    subscribeToEvent<ClientEvent<gengine::system::event::driver::input::Key_Right>>(&PlayerMotion::movePlayerRight);
    subscribeToEvent<ClientEvent<gengine::system::event::driver::input::Key_Up>>(&PlayerMotion::movePlayerUp);
    subscribeToEvent<ClientEvent<gengine::system::event::driver::input::Key_Down>>(&PlayerMotion::movePlayerDown);
    subscribeToEvent<ClientEvent<gengine::system::event::driver::input::Key_P>>(&PlayerMotion::increaseSpeed);
    subscribeToEvent<ClientEvent<gengine::system::event::driver::input::Key_O>>(&PlayerMotion::decreaseSpeed);
}

void PlayerMotion::movePlayerLeft(ClientEvent<gengine::system::event::driver::input::Key_Left> &e) {
    auto &velocities = getComponents<gengine::component::Velocity2D>();
    auto &players = getComponents<component::Player>();
    auto &playerControls = getComponents<component::PlayerControl>();
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();

    for (auto [entity, player, velocity, playerControl, remote] : gengine::Zip(players, velocities, playerControls, remotes)) {
        if (remote != e.remote)
            continue;
        if (e->state == gengine::system::event::driver::input::RELEASE)
            velocity.x += player.speed;
        else if (e->state == gengine::system::event::driver::input::PRESSED)
            velocity.x -= player.speed;
    }
}

void PlayerMotion::movePlayerRight(ClientEvent<gengine::system::event::driver::input::Key_Right> &e) {
    auto &velocities = getComponents<gengine::component::Velocity2D>();
    auto &players = getComponents<component::Player>();
    auto &playerControls = getComponents<component::PlayerControl>();
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();

    for (auto [entity, player, velocity, playerControl, remote] : gengine::Zip(players, velocities, playerControls, remotes)) {
        if (remote != e.remote)
            continue;
        if (e->state == gengine::system::event::driver::input::RELEASE)
            velocity.x -= player.speed;
        else if (e->state == gengine::system::event::driver::input::PRESSED)
            velocity.x += player.speed;
    }
}

void PlayerMotion::movePlayerUp(ClientEvent<gengine::system::event::driver::input::Key_Up> &e) {
    auto &velocities = getComponents<gengine::component::Velocity2D>();
    auto &players = getComponents<component::Player>();
    auto &playerControls = getComponents<component::PlayerControl>();
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();

    for (auto [entity, player, velocity, playerControls, remote] : gengine::Zip(players, velocities, playerControls, remotes)) {
        if (remote != e.remote)
            continue;
        if (e->state == gengine::system::event::driver::input::RELEASE)
            velocity.y += player.speed;
        else if (e->state == gengine::system::event::driver::input::PRESSED)
            velocity.y -= player.speed;
    }
}

void PlayerMotion::movePlayerDown(ClientEvent<gengine::system::event::driver::input::Key_Down> &e) {
    auto &velocities = getComponents<gengine::component::Velocity2D>();
    auto &players = getComponents<component::Player>();
    auto &playerControls = getComponents<component::PlayerControl>();
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();

    for (auto [entity, player, velocity, playerControl, remote] : gengine::Zip(players, velocities, playerControls, remotes)) {
        if (remote != e.remote)
            continue;
        if (e->state == gengine::system::event::driver::input::RELEASE)
            velocity.y -= player.speed;
        else if (e->state == gengine::system::event::driver::input::PRESSED)
            velocity.y += player.speed;
    }
}

void PlayerMotion::increaseSpeed(ClientEvent<gengine::system::event::driver::input::Key_P> &e) {
    auto &playerControls = getComponents<component::PlayerControl>();
    auto &players = getComponents<component::Player>();
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();

    for (auto [entity, player, playerControl, remote] : gengine::Zip(players, playerControls, remotes)) {
        if (remote != e.remote)
            continue;
        player.speed += 10;
    }
}

void PlayerMotion::decreaseSpeed(ClientEvent<gengine::system::event::driver::input::Key_O> &e) {
    auto &players = getComponents<component::Player>();
    auto &playerControls = getComponents<component::PlayerControl>();
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();

    for (auto [entity, player, playerControl, remote] : gengine::Zip(players, playerControls, remotes)) {
        if (remote != e.remote)
            continue;;
        player.speed = std::max(player.speed - 10, 20.f);
    }
}
} // namespace rtype::system
