/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Motions.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"

#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"

namespace gengine::system {
class Motion2D : public System<Motion2D, component::Transform2D, component::Velocity2D> {
public:
    void init(void);
    void onGameLoop(event::GameLoop &);
};

class Motion3D : public System<Motion3D, component::Transform3D, component::Velocity3D> {
public:
    void init(void);
    void onGameLoop(event::GameLoop &);
};
} // namespace gengine::system