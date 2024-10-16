/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Snapshot.cpp
*/

#include "GEngine/interface/network/systems/Snapshot.hpp"

#include "GEngine/net/msg.hpp"
#include "GEngine/net/net.hpp"
#include "GEngine/net/net_client.hpp"

namespace gengine::interface::network::system {

Snapshot::Snapshot(const snapshot_t &currentWorld)
    : m_currentWorld(currentWorld)
    , m_dummySnapshot(currentWorld) { // TODO dummy must created after components registered
}

void Snapshot::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&Snapshot::onGameLoop);
    subscribeToEvent<gengine::interface::event::NewRemoteDriver>(&Snapshot::registerSnapshot);
}

void Snapshot::onGameLoop(gengine::system::event::GameLoop &e) {
    {
        std::lock_guard<std::mutex> lock(m_netMutex);

        m_currentSnapshotId++;
        createSnapshots();
    }
    getAndSendDeltaDiff();
}

/* todo warning : mutex please */
void Snapshot::registerSnapshot(gengine::interface::event::NewRemoteDriver &e) {
    component::RemoteDriver r(e.remote);
    m_clientSnapshots.insert(std::make_pair(r, std::make_pair(m_currentSnapshotId, snapshots_t())));
    m_clientSnapshots[r].second[m_currentSnapshotId % MAX_SNAPSHOT] = m_dummySnapshot;
}

void Snapshot::destroySnapshot(gengine::interface::event::DeleteRemoteDriver &e) {
    m_clientSnapshots.erase(e.remote);
}

void Snapshot::createSnapshots(void) {
    auto &clientsSys = getSystem<gengine::interface::network::system::ServerClientsHandler>();
    for (auto &[remote, client] : clientsSys.getClients()) {
        if (client.shouldDelete())
            continue;
        auto it = m_clientSnapshots.find(remote);
        if (it == m_clientSnapshots.end())
            continue;
        it->second.second[m_currentSnapshotId % MAX_SNAPSHOT] = m_currentWorld;
    }
}

void Snapshot::getAndSendDeltaDiff(void) {
    auto &server = Network::NET::getServer();
    auto &clientsSys = getSystem<gengine::interface::network::system::ServerClientsHandler>();

    for (auto &[remote, client] : clientsSys.getClients()) {
        if (client.shouldDelete())
            continue;
        auto it = m_clientSnapshots.find(remote);
        if (it == m_clientSnapshots.end())
            continue;

        auto &[firstSnapshotId, snapshots] = it->second;
        auto lastReceived = client.getLastAck();
        auto lastId = firstSnapshotId + lastReceived;
        auto diff = m_currentSnapshotId - lastId;
        // std::cout << "diff: " << diff << " | m_currentSnapshotId: " << m_currentSnapshotId << " last id: " << lastId
        // << " UDP Last ACK: " << lastReceived << std::endl;

        auto &current = snapshots[m_currentSnapshotId % MAX_SNAPSHOT];
        auto &last = diff > MAX_SNAPSHOT ? m_dummySnapshot : snapshots[lastId % MAX_SNAPSHOT];

        std::vector<ecs::component::component_info_t> deltaDiff = getDeltaDiff(current, last);

        Network::UDPMessage msg(true, Network::SV_SNAPSHOT);
        msg.setAck(true);
        uint64_t nb_component = deltaDiff.size();
        msg.appendData(nb_component);
        for (auto &[entity, type, set, any] : deltaDiff) {
            ecs::component::ComponentTools::component_size_t size = set ? getComponentSize(type) : 0;
            NetworkComponent c(entity, getComponentId(type), size);
            msg.appendData(c);
            if (set)
                msg.appendData(toVoid(type, any), c.size);
        }

        // std::cout << "SEND: "<< msg.getSize() << " snap " << nb_component << std::endl;
        if (!server.isRunning())
            continue;
        client.getNet()->pushData(msg, true);
    }
}

std::vector<ecs::component::component_info_t> Snapshot::getDeltaDiff(const snapshot_t &snap1,
                                                                     const snapshot_t &snap2) const {
    std::vector<ecs::component::component_info_t> diff;

    for (auto &[type, any] : snap1) {
        if (!snap2.contains(type))
            THROW_ERROR(
                "the 2 world do not contain the same component - verify your component registry order"); // big error

        for (auto [e, t, s, c] : compareComponents(type, any, snap2.find(type)->second))
            diff.emplace_back(e, t, s, c);
    }
    return diff;
}
} // namespace gengine::interface::network::system
