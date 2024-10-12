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

Snapshot::Snapshot(const snapshot_t &currentWorld)
    : m_currentWorld(currentWorld)
    , m_dummySnapshot(currentWorld) { // TODO dummy must created after components registered
}

void Snapshot::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&Snapshot::onStartEngine);
    subscribeToEvent<gengine::system::event::MainLoop>(&Snapshot::onMainLoop);
}

void Snapshot::onStartEngine(gengine::system::event::StartEngine &e) {
    /* TODO : make something other than this to register clients */
    auto &eventManager = Network::NET::getEventManager();

    /* Imagine for some reason (most likely impossible) we receive the event of deleting before creating. that's
     * embarrassing */
    static std::vector<Network::NetClient *> unwantedClients = {};

    eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
        Network::Event::CT_OnClientConnect, [this](std::shared_ptr<Network::NetClient> client) {
            std::lock_guard<std::mutex> lock(m_netMutex);

            if (std::find(unwantedClients.begin(), unwantedClients.end(), client.get()) != unwantedClients.end()) {
                unwantedClients.erase(std::remove(unwantedClients.begin(), unwantedClients.end(), client.get()),
                                      unwantedClients.end());
                return;
            }
            registerClient(client);
        });
    eventManager.registerCallback<Network::NetClient *>(
        Network::Event::CT_OnClientDisconnect, [this](Network::NetClient *client) {
            std::lock_guard<std::mutex> lock(m_netMutex);

            auto it = std::find_if(m_clientSnapshots.begin(), m_clientSnapshots.end(),
                                   [client](const auto &pair) { return pair.first.getNet().get() == client; });
            if (it == m_clientSnapshots.end()) {
                unwantedClients.push_back(client);
                return;
            }
            it->first.setShouldDelete(true);
        });
}

void Snapshot::onMainLoop(gengine::system::event::MainLoop &e) {
    {
        std::lock_guard<std::mutex> lock(m_netMutex);

        m_currentSnapshotId++;
        createSnapshots();
        getAndSendDeltaDiff();
    }

    /* make something like this based on ticks */
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

/* todo warning : mutex please */
void Snapshot::registerClient(std::shared_ptr<Network::NetClient> client) {
    m_clientSnapshots.push_back(std::make_pair<>(SnapshotClient(client, m_currentSnapshotId), snapshots_t()));
    m_clientSnapshots[m_clientSnapshots.size() - 1].second[m_currentSnapshotId % MAX_SNAPSHOT] = m_dummySnapshot;
}

void Snapshot::createSnapshots(void) {
    for (auto &[client, snap] : m_clientSnapshots) {
        SnapshotClient &cli = client;
        if (client.shouldDelete()) { /* thread safe way of deleting a client from genengine */
            m_clientSnapshots.erase(
                std::remove_if(m_clientSnapshots.begin(), m_clientSnapshots.end(),
                               [&cli](const auto &pair) { return pair.first.getNet() == cli.getNet(); }),
                m_clientSnapshots.end());
            continue;
        }
        snap[m_currentSnapshotId % MAX_SNAPSHOT] = m_currentWorld;
    }
}

void Snapshot::getAndSendDeltaDiff(void) {
    auto &server = Network::NET::getServer();

    for (auto &[client, snapshots] : m_clientSnapshots) {
        /* get that info via callback OnAckUpdate */
        auto lastReceived = client.getLastAck();
        auto lastId = client.getSnapshotId() + lastReceived;
        auto diff = m_currentSnapshotId - lastId;
        // std::cout << "diff: " << diff << " | m_currentSnapshotId: " << m_currentSnapshotId << " last id: " << lastId
                  << " UDP Last ACK: " << lastReceived << std::endl;

        auto &current = snapshots[m_currentSnapshotId % MAX_SNAPSHOT];
        auto &last = diff > MAX_SNAPSHOT ? m_dummySnapshot : snapshots[lastId % MAX_SNAPSHOT];

        std::vector<ecs::component::component_info_t> deltaDiff = getDeltaDiff(current, last);

        Network::UDPMessage msg(true, Network::SV_SNAPSHOT);
        uint64_t nb_component = deltaDiff.size();
        msg.appendData(nb_component);
        for (auto &[entity, type, set, any] : deltaDiff) {
            ecs::component::ComponentTools::component_size_t size = set ? getComponentSize(type) : 0;
            NetworkComponent c(entity, getComponentId(type), size);
            msg.appendData(c);
            if (set)
                msg.appendData(toVoid(type, any), c.size);
        }

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
