/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** ServerClient.hpp
*/

#pragma once

#include "GEngine/interface/components/RemoteDriver.hpp"
#include "GEngine/interface/events/RemoteEvent.hpp"
#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/net/net.hpp"

#include <map>
#include <memory>
#include <mutex>
#include <vector>

namespace gengine::interface::network::system {
class ServerClient {
public:
    ServerClient(std::shared_ptr<Network::NetClient> client);

    std::shared_ptr<Network::NetClient> getNet(void) const;

    uint64_t getLastAck(void) const {
        return m_lastAck;
    }
    void setLastAck(uint64_t lastAck) {
        m_lastAck = lastAck;
    }

    bool shouldDelete(void) const {
        return m_shouldDelete;
    }
    void setShouldDelete(bool shouldDelete) {
        m_shouldDelete = shouldDelete;
    }

    bool isReady(void) const {
        return m_ready;
    }
    void setReady(bool ready) {
        m_ready = ready;
    }

    std::shared_ptr<Network::NetClient> getClient(void) {
        return m_client;
    }

private:
    std::shared_ptr<Network::NetClient> m_client;

    uint64_t m_lastAck = 0;
    bool m_ready = false;
    bool m_shouldDelete = false;
};

class ServerClientsHandler : public System<ServerClientsHandler> {
public:
    ServerClientsHandler();

    void init(void) override;
    void onStartEngine(gengine::system::event::StartEngine &);
    void onMainLoop(gengine::system::event::MainLoop &);

    std::unordered_map<component::RemoteDriver, ServerClient> &getClients(void) {
        return m_clients;
    }

private:
    std::unordered_map<component::RemoteDriver, ServerClient> m_clients;

    mutable std::mutex m_netMutex;
};
} // namespace gengine::interface::network::system