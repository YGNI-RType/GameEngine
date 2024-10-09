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
    char type[255];
    uint16_t size;
};

namespace gengine::interface::network::system {
void Snapshot::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&Snapshot::onStartEngine);
    subscribeToEvent<gengine::system::event::MainLoop>(&Snapshot::onMainLoop);
}

void Snapshot::onStartEngine(gengine::system::event::StartEngine &e) {
    /* TODO : make something other than this to register clients */
    auto &eventManager = Network::NET::getEventManager();

    eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
        Network::Event::CT_OnClientConnect, [this](std::shared_ptr<Network::NetClient> client) {
            std::lock_guard<std::mutex> lock(m_netMutex);

            registerClient(client);
        });
    eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
        Network::Event::CT_OnClientDisconnect, [this](std::shared_ptr<Network::NetClient> client) {
            std::lock_guard<std::mutex> lock(m_netMutex);

            auto it = std::find_if(m_clientSnapshots.begin(), m_clientSnapshots.end(),
                                   [client](const auto &pair) { return pair.first.getNet().get() == client.get(); });
            if (it == m_clientSnapshots.end())
                return;
            it->first.setShouldDelete(true);
        });
}

void Snapshot::onMainLoop(gengine::system::event::MainLoop &e) {
    std::lock_guard<std::mutex> lock(m_netMutex);

    m_currentSnapshotId++;
    createSnapshots();
    deltaDiff();
}

/* todo warning : mutex please */
void Snapshot::registerClient(std::shared_ptr<Network::NetClient> client) {
    m_clientSnapshots.push_back(std::make_pair<>(SnapshotClient(client, m_currentSnapshotId), snapshots_t()));
}

void Snapshot::createSnapshots(void) {
    for (auto &[client, snap] : m_clientSnapshots) {
        if (client.shouldDelete()) { /* thread safe way of deleting a client from genengine */
            m_clientSnapshots.erase(std::remove_if(m_clientSnapshots.begin(), m_clientSnapshots.end(),
                [&client](const auto &pair) { return pair.first.getNet() == client.getNet(); }), m_clientSnapshots.end());
            continue;
        }

        auto &cl = *client.getNet();
        size_t size = cl.getSizeIncommingData();
        for (size_t i = 0; i < size - 1; i++) {
            Network::UDPMessage msg(false, 0);
            size_t readCount;
            if (!cl.popIncommingData(msg, readCount))
                continue; /* impossible */
            /* todo : read the data and apply it to the world (another component) */
        }

        // temp
        Network::UDPMessage msg(false, 0);
        size_t readCount;
        cl.popIncommingData(msg, readCount);
        client.setLastAck(msg.getAckNumber());

        snap[m_currentSnapshotId % MAX_SNAPSHOT] = m_currentWorld;
    }
}

/* ADRIEN /!\ : we need to ensure that we send something, even when 0 bytes */
void Snapshot::deltaDiff(void) {
    for (auto &[client, snapshots] : m_clientSnapshots) {
        /* get that info via callback OnAckUpdate */
        auto lastReceived = client.getLastAck();
        auto lastId = client.getSnapshotId() + lastReceived;

        auto diff = m_currentSnapshotId - lastId;
        std::cout << "diff: " << diff << " | m_currentSnapshotId: " << m_currentSnapshotId << " last id: " << lastId
                  << " UDP Last ACK: " << lastReceived << std::endl;
        if (diff > MAX_SNAPSHOT)
            diff = MAX_SNAPSHOT; /* todo : find dummy snapshot (all 0) to send all */

        auto &current = snapshots[m_currentSnapshotId % MAX_SNAPSHOT];
        auto &last = snapshots[diff % MAX_SNAPSHOT]; // TODO check which world client is using
        std::vector<ecs::component::component_info_t> v;

        try {
            v = ecs::component::deltaDiff(current, last);
        } catch (const std::exception &e) {
        }

        Network::UDPMessage msg(true, Network::SV_SNAPSHOT);
        msg.setAck(true);
        for (auto &[entity, type, any] : v) {
            ComponentNetwork c = {.entity = entity,
                                  .size = 65432}; /* todo : found the size of the entity as well as type !!!! */
            strcpy(c.type, type.name());
            msg.appendData(c);
        }

        client.getNet()->pushData(msg, true);
    }
}
} // namespace gengine::interface::network::system