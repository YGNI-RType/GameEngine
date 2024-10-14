/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Start.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/driver/output/TextureManager.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#include "GEngine/interface/events/RemoteDriver.hpp"

namespace rtype::system {
class Start : public gengine::System<Start, gengine::system::driver::output::TextureManager> {
public:
    void init(void) override;
    void onStartEngine(gengine::system::event::StartEngine &);
    void onNewRemoteDriver(gengine::interface::event::NewRemoteDriver &e);
};
} // namespace rtype::system
