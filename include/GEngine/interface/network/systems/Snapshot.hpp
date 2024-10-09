/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** Snapshot.hpp
*/

#pragma once

#include <array>

#include "GEngine/BaseEngine.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#include "GEngine/interface/network/systems/NetworkComponent.hpp"

#define MAX_SNAPSHOT 60

namespace Network {
class NetClient;
} // namespace Network

namespace gengine::interface::network::system {

class SnapshotClient {
public:
    SnapshotClient(std::shared_ptr<Network::NetClient> client, uint64_t firsSnapshotId)
        : m_client(client)
        , m_firsSnapshotId(firsSnapshotId) {
    }

    std::shared_ptr<Network::NetClient> getNet(void) const {
        return m_client;
    }

    uint64_t getSnapshotId(void) const {
        return m_firsSnapshotId;
    }

    void setSnapshotId(uint64_t id) {
        m_firsSnapshotId = id;
    }

private:
    std::shared_ptr<Network::NetClient> m_client;
    uint64_t m_firsSnapshotId;
};

class Snapshot : public System<Snapshot> {
public:
    using snapshot_t = BaseEngine::world_t;
    using snapshots_t = std::array<snapshot_t, MAX_SNAPSHOT>;

    Snapshot(const snapshot_t &currentWorld);

    void init(void) override;
    void onStartEngine(gengine::system::event::StartEngine &);
    void onMainLoop(gengine::system::event::MainLoop &);

    void registerClient(std::shared_ptr<Network::NetClient> client);
    void createSnapshots(void);
    void getAndSendDeltaDiff(void);

private:
    const snapshot_t &m_currentWorld;
    snapshot_t m_dummySnapshot;
    std::vector<std::pair<SnapshotClient, snapshots_t>> m_clientSnapshots;
    uint64_t m_currentSnapshotId = -1;

    std::vector<ecs::component::component_info_t> getDeltaDiff(const snapshot_t &snap1, const snapshot_t &snap2) const;
};
} // namespace gengine::interface::network::system