/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MonstersAutoMotion.cpp
*/

#include "systems/MonstersAutoMotion.hpp"

#include <random>

namespace rtype::system {
void MonstersAutoMotion::init(void) {
    subscribeToEvent<gengine::system::event::MainLoop>(&MonstersAutoMotion::onMainLoop);
}

void MonstersAutoMotion::onMainLoop(gengine::system::event::MainLoop &e) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> change_chance_fork(0, 20);
    std::uniform_int_distribution<> motion_fork(-5, 5);

    auto &motions = getComponents<gengine::component::Velocity2D>();
    auto &monsters = getComponents<component::Monster>();

    for (auto [entity, motion, monster] : gengine::Zip(motions, monsters)) {
        if (change_chance_fork(gen) == 0)
            motion.x = motion_fork(gen) * monster.speed;
        if (change_chance_fork(gen) == 1)
            motion.y = motion_fork(gen) * monster.speed;
    }
}
} // namespace rtype::system
