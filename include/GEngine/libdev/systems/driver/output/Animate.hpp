/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Animate.hpp
*/

#pragma once

#include <raylib.h>

#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

namespace gengine::system::driver::output {
class Animate
    : public gengine::System<Animate, component::driver::output::Sprite, component::driver::output::Animation> {
public:
    void init(void) override;

    void onGameLoop(gengine::system::event::GameLoop &e);

private:
};
} // namespace gengine::system::driver::output