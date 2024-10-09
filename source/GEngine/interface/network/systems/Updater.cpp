/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** Updater.cpp
*/

#include "GEngine/interface/network/systems/Updater.hpp"

#include "GEngine/net/msg.hpp"
#include "GEngine/net/net.hpp"
#include "GEngine/net/net_client.hpp"
#include "GEngine/net/net_common.hpp"

namespace gengine::interface::network::system {

void Updater::init(void) {
    subscribeToEvent<gengine::system::event::MainLoop>(&Updater::onMainLoop);
}

// void Updater::onStartEngine(gengine::system::event::StartEngine &e) {
// TODO get base world ?
// }

void Updater::onMainLoop(gengine::system::event::MainLoop &e) {
    // TODO call Network::Get(SV_SNAPSHOT)
    Network::UDPMessage msg(0, 0);
    return; // TODO remove
    std::size_t readOffset = 0;

    uint64_t nb;
    msg.readContinuousData(nb, readOffset);
    for (int i = 0; i < nb; i++) {
        NetworkComponent c;
        msg.readContinuousData(c, readOffset);
        // std::cout << c.entity << " -> name: [" << c.type << "] size: " << c.size << std::endl;
        Network::byte_t component[c.size];
        msg.readData(component, readOffset, c.size);
        auto &type = getTypeindex(c.typeId); // TODO array for opti
        setComponent(c.entity, type, toAny(type, component));
    }
}
} // namespace gengine::interface::network::system