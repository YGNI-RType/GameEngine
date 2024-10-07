/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Motions.cpp
*/

#include "GEngine/libdev/systems/Motions.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"

namespace gengine::system {
void Motion2D::init(void) { subscribeToEvent<event::MainLoop>(&Motion2D::onMainLoop); }

void Motion2D::onMainLoop(event::MainLoop &e) {
    auto &transforms = getComponent<component::Transform2D>();
    auto &motions = getComponent<component::Motion2D>();

    for (auto &[entity, motion] : motions) {
        if (transforms.contains(entity)) {
            auto &transform = transforms.get(entity);
            transform.pos.x += (motion.x * e.deltaTime);
            transform.pos.y += (motion.y * e.deltaTime);
        }
    }
}

void Motion3D::init(void) { subscribeToEvent<event::MainLoop>(&Motion3D::onMainLoop); }
void Motion3D::onMainLoop(event::MainLoop &e) {
    auto &transforms = getComponent<component::Transform3D>();
    auto &motions = getComponent<component::Motion3D>();

    for (auto &[entity, motion] : motions) {
        if (transforms.contains(entity)) {
            auto &transform = transforms.get(entity);
            transform.pos.x += (motion.x * e.deltaTime);
            transform.pos.y += (motion.y * e.deltaTime);
            transform.pos.z += (motion.z * e.deltaTime);
        }
    }
}
} // namespace gengine::system
