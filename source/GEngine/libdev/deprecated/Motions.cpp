/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Motions.cpp
*/

#include "GEngine/libdev/systems/Motions.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"

namespace gengine::system {
void Motion2D::init(void) {
    subscribeToEvent<event::MainLoop>(&Motion2D::onMainLoop);
}

void Motion2D::onMainLoop(event::MainLoop &e) {
    auto &positions = getComponents<component::Position2D>();
    auto &motions = getComponents<component::Motion2D>();

    for (auto &[entity, motion] : motions) {
        if (positions.contains(entity)) {
            auto &position = positions.get(entity);
            position.x += (motion.x * e.deltaTime);
            position.y += (motion.y * e.deltaTime);
        }
    }
}

void Motion3D::init(void) {
    subscribeToEvent<event::MainLoop>(&Motion3D::onMainLoop);
}
void Motion3D::onMainLoop(event::MainLoop &e) {
    auto &positions = getComponents<component::Position3D>();
    auto &motions = getComponents<component::Motion3D>();

    for (auto &[entity, motion] : motions) {
        if (positions.contains(entity)) {
            auto &position = positions.get(entity);
            position.x += (motion.x * e.deltaTime);
            position.y += (motion.y * e.deltaTime);
            position.z += (motion.z * e.deltaTime);
        }
    }
}
} // namespace gengine::system
