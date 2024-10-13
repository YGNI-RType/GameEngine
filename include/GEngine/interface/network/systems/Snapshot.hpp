/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** Snapshot.hpp
*/

#pragma once

#include <array>
#include <mutex>

#include "GEngine/BaseEngine.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#include "GEngine/interface/network/systems/NetworkComponent.hpp"

#define MAX_SNAPSHOT 60

namespace Network {
class NetClient;
} // namespace Network

namespace gengine::interface::network::system {

class SnapshotClient {
public:
    SnapshotClient(std::shared_ptr<Network::NetClient> client, uint64_t firsSnapshotId);

    std::shared_ptr<Network::NetClient> getNet(void) const;

    uint64_t getLastAck(void) const {
        return m_lastAck;
    }
    void setLastAck(uint64_t lastAck) {
        m_lastAck = lastAck;
    }

    uint64_t getSnapshotId(void) const {
        return m_firsSnapshotId;
    }
    void setSnapshotId(uint64_t id) {
        m_firsSnapshotId = id;
    }

    bool shouldDelete(void) const {
        return m_shouldDelete;
    }
    void setShouldDelete(bool shouldDelete) {
        m_shouldDelete = shouldDelete;
    }

private:
    std::shared_ptr<Network::NetClient> m_client;
    uint64_t m_firsSnapshotId;

    uint64_t m_lastAck = 0;
    bool m_shouldDelete = false;
};

class Snapshot : public System<Snapshot> {
public:
    using snapshot_t = BaseEngine::world_t;
    using snapshots_t = std::array<snapshot_t, MAX_SNAPSHOT>;

    Snapshot(const snapshot_t &currentWorld);

    void init(void) override;
    void onStartEngine(gengine::system::event::StartEngine &);
    void onGameLoop(gengine::system::event::GameLoop &);

    void registerClient(std::shared_ptr<Network::NetClient> client);
    void createSnapshots(void);
    void getAndSendDeltaDiff(void);

private:
    const snapshot_t &m_currentWorld;
    snapshot_t m_dummySnapshot;
    std::vector<std::pair<SnapshotClient, snapshots_t>> m_clientSnapshots;
    uint64_t m_currentSnapshotId = -1;

    std::vector<ecs::component::component_info_t> getDeltaDiff(const snapshot_t &snap1, const snapshot_t &snap2) const;

    mutable std::mutex m_netMutex;
};
} // namespace gengine::interface::network::system