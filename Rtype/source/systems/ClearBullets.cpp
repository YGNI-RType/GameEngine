/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** BackgroundAutoMotion.cpp
*/

#include "systems/ClearBullets.hpp"
#include "ecs/system/Base.hpp"

namespace rtype::system {
void ClearBullets::init(void) {
    subscribeToEvent<gengine::system::event::MainLoop>(&ClearBullets::onMainLoop);
}

void ClearBullets::onMainLoop(gengine::system::event::MainLoop &e) {
    // clearFires();
    clearBullets();
}

// void ClearBullets::clearFires(void) {
//     auto &fires = getComponents<component::Fire>();
//     auto &animations = getComponents<gengine::component::driver::output::Animation>();

//     for (auto [entity, fire, animation] : gengine::Zip(fires, animations))
//         if (animation.currentFrame == animation.nbFrames - 1)
//             killEntity(entity);
// }

void ClearBullets::clearBullets(void) {
    auto &bullets = getComponents<component::Bullet>();
    auto &transforms = getComponents<gengine::component::Transform2D>();

    for (auto [entity, bullet, transform] : gengine::Zip(bullets, transforms))
        if (transform.pos.x > 1280)
            killEntity(entity);
}
} // namespace rtype::system
