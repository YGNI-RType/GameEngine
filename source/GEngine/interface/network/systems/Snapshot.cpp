/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Snapshot.cpp
*/

#include "GEngine/interface/network/systems/Snapshot.hpp"

#include "GEngine/net/msg.hpp"
#include "GEngine/net/net.hpp"

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
    registerClient();
    createSnapshots();
}

void Snapshot::onMainLoop(gengine::system::event::MainLoop &e) {
    m_currentSnapshotId++;
    createSnapshots();
    deltaDiff();
}

void Snapshot::registerClient(void) {
    m_clientSnapshots.push_back(snapshots_t());
}

void Snapshot::createSnapshots(void) {
    for (auto &snap : m_clientSnapshots)
        snap[m_currentSnapshotId % MAX_SNAPSHOT] = m_currentWorld;
}

void Snapshot::deltaDiff(void) {
    for (auto &snapshots : m_clientSnapshots) {
        auto &current = snapshots[m_currentSnapshotId % MAX_SNAPSHOT];
        auto &last = snapshots[(m_currentSnapshotId - 1) % MAX_SNAPSHOT]; // TODO check which world client is using
        auto v = ecs::component::deltaDiff(current, last);
        // for (auto &[e, t, c] : v)
        //     std::cout << e << " -> " << t.name() << std::endl;
        // if (v.size())
        //     std::cout << std::endl;
        //TODO msg = create UDPMessage(v)
        if (!v.size())
            break;
        Network::UDPMessage msg(true, Network::SV_SNAPSHOT);
        msg.setAck(true);
        for (auto &[entity, type, any]: v) {
            ComponentNetwork c = {.entity = 123456789, .size = 65432};
            strcpy(c.type, type.name());
            msg.appendData(c);
            break;

            // msg.appendData(any);
        }
        auto &server = Network::NET::getServer();

        Network::NET::sleep(300);
        if (!server.isRunning())
            continue;

        // Network::UDPMessage msg(true, 4);
        // const char *data = "Coucou je suis le serveir !!";
        // msg.writeData(static_cast<const void *>(data), std::strlen(data));

        server.sendToAllClients(msg);

        // msg.appendData()
        // send msg
        // TODO order send to network
    }
}
} // namespace gengine::interface::network::system