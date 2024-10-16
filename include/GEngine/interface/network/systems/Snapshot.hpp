/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : Snapshot.hpp
**  Create at   : 2024-10-15 04:51
**  Author      : AUTHOR
**  Description : DESCRIPTION
** ═══════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include <array>
#include <mutex>

#include "GEngine/BaseEngine.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#include "GEngine/interface/events/RemoteDriver.hpp"
#include "GEngine/interface/network/systems/NetworkComponent.hpp"
#include "GEngine/interface/network/systems/ServerClient.hpp"

#define MAX_SNAPSHOT 60

namespace Network {
class NetClient;
} // namespace Network

namespace gengine::interface::network::system {

class Snapshot : public System<Snapshot, gengine::interface::network::system::ServerClientsHandler> {
public:
    using snapshot_t = BaseEngine::world_t;
    using snapshots_t = std::array<snapshot_t, MAX_SNAPSHOT>;

    Snapshot(const snapshot_t &currentWorld);

    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);

    void registerSnapshot(gengine::interface::event::NewRemoteDriver &e);
    void destroySnapshot(gengine::interface::event::DeleteRemoteDriver &e);
    void createSnapshots(void);
    void getAndSendDeltaDiff(void);

private:
    const snapshot_t &m_currentWorld;
    snapshot_t m_dummySnapshot;
    std::unordered_map<component::RemoteDriver, std::pair<uint64_t, snapshots_t>> m_clientSnapshots;
    uint64_t m_currentSnapshotId = -1;

    std::vector<ecs::component::component_info_t> getDeltaDiff(const snapshot_t &snap1, const snapshot_t &snap2) const;

    mutable std::mutex m_netMutex;
};
} // namespace gengine::interface::network::system