/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Motions.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Motions.hpp"
#include "GEngine/libdev/components/Positions.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"

namespace gengine::system {
class Motion2D : public System<Motion2D, component::Position2D, component::Motion2D> {
public:
    void init(void);
    void onMainLoop(event::MainLoop &);
};

class Motion3D : public System<Motion3D, component::Position3D, component::Motion3D> {
public:
    void init(void);
    void onMainLoop(event::MainLoop &);
};
} // namespace gengine::system