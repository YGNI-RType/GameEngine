/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** PlayerShoot.hpp
*/

#pragma once

#include "GEngine/libdev/components/HitBoxs.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "components/PlayerControl.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/driver/input/Keyboard.hpp"

namespace rtype::system {
class PlayerShoot : public gengine::System<PlayerShoot, component::PlayerControl, gengine::component::Transform2D,
                                           gengine::component::HitBoxSquare2D> {
public:
    void init(void) override;
    void shoot(gengine::system::event::driver::input::Key_B &);
};
} // namespace rtype::system
