/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** RemoteDriver.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/interface/components/RemoteDriver.hpp"

namespace gengine::interface::event {
    struct NewRemoteDriver: gengine::Event {
        component::RemoteDriver remote;
        NewRemoteDriver(component::RemoteDriver &remote): remote(remote) {}
        NewRemoteDriver(const component::RemoteDriver &&remote): remote(remote) {}
    };

    struct DeleteRemoteDriver: gengine::Event {
        component::RemoteDriver remote;
        DeleteRemoteDriver(component::RemoteDriver remote): remote(remote) {}
        DeleteRemoteDriver(component::RemoteDriver &remote): remote(remote) {}
        DeleteRemoteDriver(const component::RemoteDriver &remote): remote(remote) {}
    };
}
