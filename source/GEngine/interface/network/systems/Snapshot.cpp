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
SnapshotClient::SnapshotClient(std::shared_ptr<Network::NetClient> client, uint64_t firsSnapshotId)
    : m_client(client)
    , m_firsSnapshotId(firsSnapshotId) {
}

std::shared_ptr<Network::NetClient> SnapshotClient::getNet(void) const {
    return m_client;
}

uint64_t SnapshotClient::getSnapshotId(void) const {
    return m_firsSnapshotId;
}

void SnapshotClient::setSnapshotId(uint64_t id) {
    m_firsSnapshotId = id;
}

Snapshot::Snapshot(const snapshot_t &currentWorld)
    : m_currentWorld(currentWorld)
    , m_dummySnapshot(currentWorld) { // TODO dummy must created after components registered
}

void Snapshot::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&Snapshot::onStartEngine);
    subscribeToEvent<gengine::system::event::MainLoop>(&Snapshot::onMainLoop);
}

void Snapshot::onStartEngine(gengine::system::event::StartEngine &e) {
    Network::NET::initServer(*this);
}

void Snapshot::onMainLoop(gengine::system::event::MainLoop &e) {
    m_currentSnapshotId++;
    createSnapshots();
    getAndSendDeltaDiff();

    // /* todo:  ça serait pas vraiment snapshot, plus un systeme network donc */
    Network::NET::sleep(300);
}

/* todo warning : mutex please */
void Snapshot::registerClient(std::shared_ptr<Network::NetClient> client) {
    m_clientSnapshots.push_back(std::make_pair<>(SnapshotClient(client, m_currentSnapshotId), snapshots_t()));
    m_clientSnapshots[m_clientSnapshots.size() - 1].second[m_currentSnapshotId % MAX_SNAPSHOT] = m_dummySnapshot;
}

void Snapshot::createSnapshots(void) {
    for (auto &[client, snap] : m_clientSnapshots) {
        if (client.getNet()->isDisconnected()) { /* thread safe way of deleting a client from genengine */
            m_clientSnapshots.erase(
                std::remove_if(m_clientSnapshots.begin(), m_clientSnapshots.end(),
                               [&client](const auto &pair) { return pair.first.getNet() == client.getNet(); }),
                m_clientSnapshots.end());
            continue;
        }
        snap[m_currentSnapshotId % MAX_SNAPSHOT] = m_currentWorld;
    }
}

void Snapshot::getAndSendDeltaDiff(void) {
    auto &server = Network::NET::getServer();

    for (auto &[client, snapshots] : m_clientSnapshots) {
        auto lastReceived = client.getNet()->getChannel().getLastACKPacketId();
        auto lastId = client.getSnapshotId() + lastReceived;
        auto diff = m_currentSnapshotId - lastId;
        std::cout << "diff: " << diff << " | m_currentSnapshotId: " << m_currentSnapshotId << " last id: " << lastId
                  << " UDP Last ACK: " << lastReceived << std::endl;

        auto &current = snapshots[m_currentSnapshotId % MAX_SNAPSHOT];
        auto &last = diff > MAX_SNAPSHOT ? m_dummySnapshot : snapshots[lastId % MAX_SNAPSHOT];

        std::vector<ecs::component::component_info_t> deltaDiff = getDeltaDiff(current, last);
        if (diff > MAX_SNAPSHOT || !diff)
            deltaDiff = getDeltaDiff(current, m_dummySnapshot);
        else
            deltaDiff = getDeltaDiff(current, snapshots[lastId % MAX_SNAPSHOT]);

        uint64_t nb_component = deltaDiff.size();
        Network::UDPMessage msg(true, Network::SV_SNAPSHOT);
        msg.setAck(true);
        msg.appendData(nb_component);
        for (auto &[entity, type, any] : deltaDiff) {
            NetworkComponent c(entity, getComponentId(type),
                               getComponentSize(type)); /* todo : found the size of the entity as well as type !!!! */
            msg.appendData(c);
            msg.writeData(toVoid(type, any), c.size);
        }

        if (!server.isRunning())
            continue;

        server.sendToClient(*client.getNet(), msg);
    }
}

std::vector<ecs::component::component_info_t> Snapshot::getDeltaDiff(const snapshot_t &snap1,
                                                                     const snapshot_t &snap2) const {
    std::vector<ecs::component::component_info_t> diff;

    for (auto &[type, any] : snap1) {
        if (!snap2.contains(type))
            THROW_ERROR(
                "the 2 world do not contain the same component - verify your component registry order"); // big error

        for (auto [e, t, c] : compareComponents(type, any, snap2.find(type)->second))
            diff.emplace_back(e, t, c);
    }
    return diff;
}
} // namespace gengine::interface::network::system
