/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** PlayerMotion.hpp
*/

#pragma once

#include "components/Player.hpp"
#include "components/PlayerControl.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/driver/input/Keyboard.hpp"

#include "GEngine/interface/components/RemoteDriver.hpp" // ClientEvent
#include "GEngine/interface/events/RemoteEvent.hpp"      // ClientEvent

namespace rtype::system {

template <typename T>
using ClientEvent = gengine::interface::network::event::RemoteEvent<T>;

class PlayerMotion : public gengine::System<PlayerMotion, gengine::component::Velocity2D, component::PlayerControl,
                                            component::Player, gengine::interface::component::RemoteDriver> {
public:
    void init(void) override;
    void movePlayerLeft(ClientEvent<gengine::system::event::driver::input::Key_Left> &);
    void movePlayerRight(ClientEvent<gengine::system::event::driver::input::Key_Right> &);
    void movePlayerUp(ClientEvent<gengine::system::event::driver::input::Key_Up> &);
    void movePlayerDown(ClientEvent<gengine::system::event::driver::input::Key_Down> &);
    void increaseSpeed(ClientEvent<gengine::system::event::driver::input::Key_P> &);
    void decreaseSpeed(ClientEvent<gengine::system::event::driver::input::Key_O> &);
};
} // namespace rtype::system
