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
#include "GEngine/libdev/components/SpanLife.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"

#define BULLET_SPEED 10

namespace rtype::system {
void PlayerShoot::init(void) {
    subscribeToEvent<gengine::interface::network::event::RemoteEvent<event::Shoot>>(&PlayerShoot::shoot);
    subscribeToEvent<gengine::interface::event::NewRemoteDriver>(&PlayerShoot::newShooter);
    subscribeToEvent<gengine::interface::event::DeleteRemoteDriver>(&PlayerShoot::deleteShooter);
    subscribeToEvent<gengine::system::driver::input::KeySpaceEvent>(&PlayerShoot::bulletSound);
}

void PlayerShoot::newShooter(gengine::interface::event::NewRemoteDriver &e) {
    m_shooterMap.insert({e.remote, shoot_infos_t()});
}
void PlayerShoot::deleteShooter(gengine::interface::event::DeleteRemoteDriver &e) {
    m_shooterMap.erase(e.remote);
}

void PlayerShoot::shoot(gengine::interface::network::event::RemoteEvent<event::Shoot> &e) {
    auto it = m_shooterMap.find(e.remote);

    if (it == m_shooterMap.end())
        return;
    auto &[state, lastCharge] = it->second;
    if (e->state == event::Shoot::REST && state == event::Shoot::CHARGING) {
        state = event::Shoot::REST;
        if (getChargeDuration(lastCharge) > 500)
            shootBeam(e.remote, (getChargeDuration(lastCharge) - 500) / 100);
        return;
    }
    if (e->state == event::Shoot::CHARGING && state == event::Shoot::REST) {
        lastCharge = std::chrono::system_clock::now();
        state = event::Shoot::CHARGING;
        // spawnEntity(
        //     gengine::component::Transform2D({0, 0}, {2, 2}), gengine::component::Velocity2D(0, 0),
        //     gengine::component::driver::output::Drawable(2),
        //     gengine::component::driver::output::Sprite("r-typesheet1.gif", Rectangle{0, 51, 32, 32}, WHITE),
        //     gengine::component::driver::output::Animation(
        //         "r-typesheet1.json/charging", 0.1f, gengine::component::driver::output::AnimationTrack::Forward, 2));
        shootBullet(e.remote);
    }
}

void PlayerShoot::bulletSound(gengine::system::driver::input::KeySpaceEvent &e) {
    auto &soundMan = getSystem<gengine::system::driver::output::SoundManager>();
    if (e.state == gengine::system::driver::input::InputState::PRESSED)
        PlaySound(soundMan.get("shoot.mp3"));
}

void PlayerShoot::shootBullet(const gengine::interface::component::RemoteDriver &from) {
    auto &players = getComponents<gengine::interface::component::RemoteDriver>();
    auto &transforms = getComponents<gengine::component::Transform2D>();

    for (auto [entity, player, transform] : gengine::Zip(players, transforms)) {
        if (player != from)
            continue;
        spawnEntity(component::Bullet(from.getUUIDString()),
                    gengine::component::Transform2D({transform.pos.x + 93, transform.pos.y + 22}, {2, 2}, 0),
                    gengine::component::Velocity2D(BULLET_SPEED, 0),
                    gengine::component::driver::output::Sprite("r-typesheet1.gif", Rectangle{248, 85, 17, 12}, WHITE),
                    gengine::component::driver::output::Drawable(1), gengine::component::HitBoxSquare2D(17, 12));
        return;
    }
}

void PlayerShoot::shootBeam(const gengine::interface::component::RemoteDriver &from, int bulletScale) {
    auto &players = getComponents<gengine::interface::component::RemoteDriver>();
    auto &transforms = getComponents<gengine::component::Transform2D>();

    for (auto [entity, player, transform] : gengine::Zip(players, transforms)) {
        if (player != from)
            continue;
        spawnBeam(transform.pos, player.getUUIDString(), bulletScale);
        return;
    }
}

void PlayerShoot::spawnBeam(const gengine::component::Transform2D &tr, const std::string &from, int bulletScale) {
    Rectangle rect;
    gengine::Vect2 pos({tr.pos.x + 50, tr.pos.y + 22});

    switch (bulletScale) {
    case 0:
        rect = {231, 103, 17, 12};
        break;
    case 1:

        rect = {199, 180, 33, 12};
        break;
    case 2:
        rect = {167, 136, 49, 14};
        break;
    case 3:
        rect = {135, 154, 65, 14};
        break;
    default:
        rect = {104, 170, 81, 16};
        break;
    }

    spawnEntity(component::Bullet(from, true), gengine::component::Transform2D(pos, {2, 2}),
                gengine::component::Velocity2D(BULLET_SPEED * 2, 0),
                gengine::component::HitBoxSquare2D(rect.width, rect.height),
                gengine::component::driver::output::Sprite("r-typesheet1.gif", rect),
                gengine::component::driver::output::Animation("r-typesheet1.json/beam", 0.06f),
                gengine::component::driver::output::Drawable(1));
}

long PlayerShoot::getChargeDuration(const std::chrono::time_point<std::chrono::system_clock> &lastCharge) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastCharge).count();
}

} // namespace rtype::system
