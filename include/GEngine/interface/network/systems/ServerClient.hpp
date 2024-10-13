/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** ServerClient.hpp
*/

#pragma once

#include "GEngine/interface/network/events/ClientEvent.hpp"
#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/net/net.hpp"
#include "GEngine/interface/components/RemoteDriver.hpp"

#include <vector>
#include <memory>
#include <mutex>
#include <map>

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

    // uint64_t getSnapshotId(void) const {
    //     return m_firsSnapshotId;
    // }
    // void setSnapshotId(uint64_t id) {
    //     m_firsSnapshotId = id;
    // }

    bool shouldDelete(void) const {
        return m_shouldDelete;
    }
    void setShouldDelete(bool shouldDelete) {
        m_shouldDelete = shouldDelete;
    }

private:
    std::shared_ptr<Network::NetClient> m_client;

    uint64_t m_lastAck = 0;
    bool m_shouldDelete = false;
};

class ServerClientsHandler : public System<ServerClientsHandler> {
public:
    ServerClientsHandler();

    void init(void) override;
    void onStartEngine(gengine::system::event::StartEngine &);
    void onMainLoop(gengine::system::event::MainLoop &);

    std::map<component::RemoteDriver, ServerClient> &getClients(void) {
        return m_clients;
    }

private:
    std::map<component::RemoteDriver, ServerClient> m_clients;

    mutable std::mutex m_netMutex;
};
}