/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** NetworkMainLoop.hpp
*/

#pragma once

#include <array>

#include "GEngine/BaseEngine.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#define MAX_SNAPSHOT 60

namespace gengine::interface::network::system {
class Snapshot : public System<Snapshot> {
public:
    using snapshot_t = BaseEngine::world_t;
    using snapshots_t = std::array<snapshot_t, MAX_SNAPSHOT>;

    Snapshot(const snapshot_t &currentWorld)
        : m_currentWorld(currentWorld) {
    }

    void init(void) override;
    void onStartEngine(gengine::system::event::StartEngine &);
    void onMainLoop(gengine::system::event::MainLoop &);

    void registerClient(void);
    void createSnapshots(void);
    void deltaDiff(void);

private:
    const snapshot_t &m_currentWorld;
    std::vector<snapshots_t> m_clientSnapshots;
    std::size_t m_currentSnapshotId = 0;
};
} // namespace gengine::interface::network::system