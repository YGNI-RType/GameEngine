/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** RemoteEvent.hpp
*/

#pragma once

#include "GEngine/interface/network/events/RemoteEvent.hpp"
#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/net/net.hpp"
#include "GEngine/interface/network/systems/ServerClient.hpp"

#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>

namespace gengine::interface::network::system {

class ServerClient {
public:
    ServerClient(std::shared_ptr<Network::NetClient> client);

    std::shared_ptr<Network::NetClient> getNet(void) const;

    bool shouldDelete(void) const;
    void setShouldDelete(bool shouldDelete);

private:
    std::shared_ptr<Network::NetClient> m_client;
    bool m_shouldDelete = false;
};

template <class... Events>
class ServerEventReceiver : public System<ServerEventReceiver<Events...>, gengine::interface::network::system::ServerClientsHandler> {
public:
    ServerEventReceiver();

    void init(void) override;
    void onMainLoop(gengine::system::event::MainLoop &e);

private:
    template <typename T>
    void dynamicPublish(void);

    std::uint64_t m_id = 0;
    const Network::NetServer &m_server;
    std::unordered_map<std::uint64_t, std::pair<std::function<void(void *)>, size_t>> m_eventsCallbacks;
    mutable std::mutex m_netMutex;
};

#include "ServerEventReceiver.inl"

} // namespace gengine::interface::network::system
