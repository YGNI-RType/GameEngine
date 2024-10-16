/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** Updater.cpp
*/

#include "GEngine/interface/network/systems/Updater.hpp"

#include "GEngine/net/net.hpp"
#include "GEngine/net/net_client.hpp"
#include "GEngine/net/net_common.hpp"

namespace gengine::interface::network::system {

void Updater::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&Updater::onGameLoop);
}

// void Updater::onStartEngine(gengine::system::event::StartEngine &e) {
// TODO get base world ?
// }

void Updater::onGameLoop(gengine::system::event::GameLoop &e) {
    Network::CLNetClient &cl = Network::NET::getClient();

    size_t size = cl.getSizeIncommingData(Network::SV_SNAPSHOT, true);
    for (size_t i = 0; i < size; i++) {
        Network::UDPMessage msg(true, Network::SV_SNAPSHOT);
        size_t readCount;
        if (!cl.popIncommingData(msg, readCount, true))
            continue;
        handleSnapshotMsg(msg, readCount);
    }
}

void Updater::handleSnapshotMsg(Network::UDPMessage &msg, size_t readCount) {
    uint64_t nb;
    msg.readContinuousData(nb, readCount);
    // std::cout << "RECV: "<< msg.getSize() << " snap " << nb << std::endl;
    for (int i = 0; i < nb; i++) {
        NetworkComponent c;
        msg.readContinuousData(c, readCount);
        std::vector<Network::byte_t> component(c.size);
        msg.readData(component.data(), readCount, c.size);
        readCount += c.size;
        auto &type = getTypeindex(c.typeId); // TODO array for opti
        if (c.size)
            setComponent(c.entity, type, toAny(type, component.data()));
        else
            unsetComponent(c.entity, type);
    }
}
} // namespace gengine::interface::network::system