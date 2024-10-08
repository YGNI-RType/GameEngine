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

struct ComponentNetwork {
    uint64_t entity;
    uint16_t type;
    uint16_t size;
};

namespace gengine::interface::network::system {
void Snapshot::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&Snapshot::onStartEngine);
    subscribeToEvent<gengine::system::event::MainLoop>(&Snapshot::onMainLoop);
}

void Snapshot::onStartEngine(gengine::system::event::StartEngine &e) {
    /* todo : faudrait renommer le nom du système, ça colle plus à serveur ducoup */
    Network::NET::initServer(*this);
    m_dummySnapshot = m_currentWorld;
}

void Snapshot::onMainLoop(gengine::system::event::MainLoop &e) {
    m_currentSnapshotId++;
    createSnapshots();
    deltaDiff();

    /* todo:  ça serait pas vraiment snapshot, plus un systeme network donc */
    Network::NET::sleep(300);
}

/* todo warning : mutex please */
void Snapshot::registerClient(std::shared_ptr<Network::NetClient> client) {
    m_clientSnapshots.push_back(std::make_pair<>(SnapshotClient(client, m_currentSnapshotId), snapshots_t()));
    m_clientSnapshots.at(m_clientSnapshots.size() - 1).second[m_currentSnapshotId % MAX_SNAPSHOT] = m_dummySnapshot;
    std::cout << "c:" << m_currentSnapshotId << std::endl;
}

void Snapshot::createSnapshots(void) {
    for (auto &[client, snap] : m_clientSnapshots) {
        if (client.getNet()->isDisconnected()) { /* thread safe way of deleting a client from genengine */
            m_clientSnapshots.erase(std::remove_if(m_clientSnapshots.begin(), m_clientSnapshots.end(),
                [&client](const auto &pair) { return pair.first.getNet() == client.getNet(); }), m_clientSnapshots.end());
            continue;
        }
        snap[m_currentSnapshotId % MAX_SNAPSHOT] = m_currentWorld;
    }
}

/* ADRIEN /!\ : we need to ensure that we send something, even when 0 bytes */
void Snapshot::deltaDiff(void) {
    auto &server = Network::NET::getServer();

    for (auto &[client, snapshots] : m_clientSnapshots) {
        auto lastReceived = client.getNet()->getChannel().getLastACKPacketId();
        auto lastId = client.getSnapshotId() + lastReceived;

        auto &current = snapshots[m_currentSnapshotId % MAX_SNAPSHOT];

        auto diff = m_currentSnapshotId - lastId;
        std::cout << "diff: " << diff << " | m_currentSnapshotId: " << m_currentSnapshotId << " last id: " << lastId << " UDP Last ACK: " << lastReceived << std::endl;
        std::vector<ecs::component::component_info_t> v;
        if (diff > MAX_SNAPSHOT || !diff) {
            // diff = MAX_SNAPSHOT; /* todo : find dummy snapshot (all 0) to send all */
            v = ecs::component::deltaDiff(current, m_tools, m_dummySnapshot);
        } else {
            auto &last = snapshots[lastId % MAX_SNAPSHOT]; // TODO check which world client is using
            v = ecs::component::deltaDiff(current, m_tools, last);
        }
        // try {
        // } catch (const std::exception &e) {
        // }
        uint64_t nb_component = v.size();
        if (!nb_component)
            break;
        Network::UDPMessage msg(true, Network::SV_SNAPSHOT);
        msg.setAck(true);
        msg.appendData(nb_component);
        for (auto &[entity, type, any]: v) {
            auto &[d, s, c, info] = m_tools.find(type)->second;
            ComponentNetwork cn = {.entity = entity, .type = info.first, .size = info.second}; /* todo : found the size of the entity as well as type !!!! */
            // strcpy(c.type, type.name());
            std::cout << nb_component << " " << info.second << std::endl;
            msg.appendData(cn);
        }

        if (!server.isRunning())
            continue;

        server.sendToClient(*client.getNet(), msg);
    }
}
} // namespace gengine::interface::network::system