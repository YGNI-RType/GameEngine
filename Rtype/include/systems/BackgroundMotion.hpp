/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** BackgroundAutoMotion.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"

#include "components/Background.hpp"

namespace rtype::system {
class BackgroundMotion : public gengine::System<BackgroundMotion, gengine::component::Velocity2D,
                                                gengine::component::Transform2D, component::Background> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
    void updateBackgroundSpeed(void);
};
} // namespace rtype::system
