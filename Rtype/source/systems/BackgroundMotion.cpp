/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** BackgroundAutoMotion.cpp
*/

#include "systems/BackgroundMotion.hpp"

namespace rtype::system {
void BackgroundMotion::init(void) {
    // TODO replace by an other event
    // This is for update speed for simulate an hyper speed for example
    // subscribeToEvent<gengine::system::event::GameLoop>(&BackgroundAutoMotion::updateBackgroundSpeed);

    // TODO doesn't work because background is create after
    // subscribeToEvent<gengine::system::event::StartEngine>(&BackgroundMotion::updateBackgroundSpeed);

    subscribeToEvent<gengine::system::event::GameLoop>(&BackgroundMotion::onGameLoop);
}

void BackgroundMotion::onGameLoop(gengine::system::event::GameLoop &e) {
    auto &transforms = getComponents<gengine::component::Transform2D>();
    auto &backgrounds = getComponents<component::Background>();

    for (auto [entity, transform, background] : gengine::Zip(transforms, backgrounds))
        if (transform.pos.x < -1119 * 3.48 - 1)
            transform.pos.x = 1119 * 3.48;
}

void BackgroundMotion::updateBackgroundSpeed(void) {
    auto &motions = getComponents<gengine::component::Velocity2D>();
    auto &backgrounds = getComponents<component::Background>();

    for (auto [entity, motion, background] : gengine::Zip(motions, backgrounds))
        motion.x = background.speed;
}
} // namespace rtype::system
