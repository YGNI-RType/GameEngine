/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : ServerEventReceiver.hpp
**  Create at   : 2024-10-15 04:51
**  Author      : AUTHOR
**  Description : This system catch all RemoteEvent send by ClientEventPublisher
                    and publis them to GameEngine event Bus.
** ═══════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "GEngine/interface/events/RemoteEvent.hpp"
#include "GEngine/interface/network/systems/ServerClient.hpp"
#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/net/net.hpp"

#include "GEngine/interface/components/RemoteDriver.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace gengine::interface::network::system {

template <class... Events>
class ServerEventReceiver
    : public System<ServerEventReceiver<Events...>, gengine::interface::network::system::ServerClientsHandler> {
public:
    ServerEventReceiver();

    void init(void) override;
    void onMainLoop(gengine::system::event::MainLoop &e);

private:
    template <typename T>
    void dynamicPublish(void);

    std::uint64_t m_id = 0;
    const Network::NetServer &m_server;
    std::unordered_map<std::uint64_t, std::pair<std::function<void(void *, component::RemoteDriver &)>, size_t>>
        m_eventsCallbacks;
    mutable std::mutex m_netMutex;
};

#include "ServerEventReceiver.inl"

} // namespace gengine::interface::network::system
