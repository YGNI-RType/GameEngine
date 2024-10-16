/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Start.hpp
*/

#pragma once

#include "GEngine/interface/components/RemoteDriver.hpp"
#include "GEngine/interface/events/RemoteDriver.hpp"
#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/driver/output/TextureManager.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

namespace rtype::system {
class Start : public gengine::System<Start, gengine::system::driver::output::TextureManager,
                                     gengine::interface::component::RemoteDriver> {
public:
    void init(void) override;
    void onStartEngine(gengine::system::event::StartEngine &);
    void onNewRemoteDriver(gengine::interface::event::NewRemoteDriver &);
    void onDeleteRemoteDriver(gengine::interface::event::DeleteRemoteDriver &e);

private:
    size_t m_nbPlayer = 0;
};
} // namespace rtype::system
