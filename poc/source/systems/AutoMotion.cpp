/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Start.hpp
*/

#include "systems/AutoMotion.hpp"

#include "GEngine/libdev/components/Velocities.hpp"

#include <random>

namespace hagarioop::systems {
void AutoMotion::init(void) {
    subscribeToEvent<gengine::system::event::MainLoop>(&AutoMotion::onMainLoop);
    subscribeToEvent<gengine::system::event::driver::input::Key_Left>(&AutoMotion::onKeyLeft);
    subscribeToEvent<gengine::system::event::driver::input::Key_Right>(&AutoMotion::onKeyRight);
    subscribeToEvent<gengine::system::event::driver::input::Key_Up>(&AutoMotion::onKeyUp);
    subscribeToEvent<gengine::system::event::driver::input::Key_Down>(&AutoMotion::onKeyDown);
}

void AutoMotion::onMainLoop(gengine::system::event::MainLoop &e) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> change_chance_fork(0, 20);
    std::uniform_int_distribution<> motion_fork(-50, 50);

    auto &motions = getComponents<gengine::component::Velocity2D>();

    for (auto &[entity, motion] : motions) {
        if (!entity)
            continue;
        if (change_chance_fork(gen) == 0)
            motion.x = motion_fork(gen);
        if (change_chance_fork(gen) == 1)
            motion.y = motion_fork(gen);
    }
}

void AutoMotion::onKeyLeft(gengine::system::event::driver::input::Key_Left &e) {
    auto &motions = getComponents<gengine::component::Velocity2D>();
    if (e.state == gengine::system::event::driver::input::RELEASE)
        motions.get(0).x += 1000;
    else if (e.state == gengine::system::event::driver::input::PRESSED)
        motions.get(0).x -= 1000;
}

void AutoMotion::onKeyRight(gengine::system::event::driver::input::Key_Right &e) {
    auto &motions = getComponents<gengine::component::Velocity2D>();
    if (e.state == gengine::system::event::driver::input::RELEASE)
        motions.get(0).x -= 1000;
    else if (e.state == gengine::system::event::driver::input::PRESSED)
        motions.get(0).x += 1000;
}

void AutoMotion::onKeyUp(gengine::system::event::driver::input::Key_Up &e) {
    auto &motions = getComponents<gengine::component::Velocity2D>();
    if (e.state == gengine::system::event::driver::input::RELEASE)
        motions.get(0).y += 1000;
    else if (e.state == gengine::system::event::driver::input::PRESSED)
        motions.get(0).y -= 1000;
}

void AutoMotion::onKeyDown(gengine::system::event::driver::input::Key_Down &e) {
    auto &motions = getComponents<gengine::component::Velocity2D>();
    if (e.state == gengine::system::event::driver::input::RELEASE)
        motions.get(0).y -= 1000;
    else if (e.state == gengine::system::event::driver::input::PRESSED)
        motions.get(0).y += 1000;
}
} // namespace hagarioop::systems