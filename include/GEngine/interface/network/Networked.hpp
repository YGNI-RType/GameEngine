#pragma once

#include "GEngine/driver/Engine.hpp"
#include "GEngine/game/Engine.hpp"
#include "GEngine/interface/Base.hpp"
#include "GEngine/libdev/systems/MainLoop.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"

#include "GEngine/interface/network/systems/Updater.hpp"

#include "GEngine/interface/components/RemoteDriver.hpp"
#include "GEngine/interface/network/systems/Snapshot.hpp"
#include "GEngine/net/events/connection.hpp"

#include "GEngine/net/msg.hpp"
#include "GEngine/net/net.hpp"
#include "GEngine/net/structs/msg_udp_structs.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

namespace gengine::interface::network {

class Networked : public Base {
public:
    Networked(driver::Engine &driverEngine, game::Engine &gameEngine, const std::string &ip = "", uint16_t port = 0,
              bool block = false)
        : m_gameEngine(gameEngine)
        , m_driverEngine(driverEngine)
        , m_ip(ip)
        , m_port(port)
        , m_block(block) {

        Network::NET::init();
        Network::Event::Manager &em = Network::NET::getEventManager();
        registerComponent<gengine::interface::component::RemoteDriver>();
#ifdef GEngine_Server
        Network::NET::initServer();
        m_gameEngine.registerSystem<system::Snapshot>(gameEngine.getWorld());
        m_gameEngine.registerSystem<gengine::interface::network::system::ServerClientsHandler>();
#elif GEngine_Client
        Network::NET::initClient();
        em.addEvent<Network::Event::ConnectInfo>(Network::Event::CONNECT, Network::Event::ConnectInfo(ip, port));
        m_driverEngine.registerSystem<gengine::interface::network::system::Updater>();
#endif
        Network::NET::start();
        m_driverEngine.registerSystem<gengine::system::AutoMainLoop>();
        m_gameEngine.registerSystem<gengine::system::AutoMainLoop>();
    }

    ~Networked() {
        Network::NET::stop();
        Network::NET::getClient().disconnectFromServer();
    }

#ifdef GEngine_Server
    void run() override {
        m_gameEngine.start();
        m_gameEngine.compute();
    }
#else
    void run() override {
        m_driverEngine.start();
        m_driverEngine.compute();
    }
#endif
    template <typename T>
    void registerComponent(void) {
        m_gameEngine.registerComponent<T>();
        m_driverEngine.registerComponent<T>();
    }

private:
    game::Engine &m_gameEngine;
    driver::Engine &m_driverEngine;
    const std::string m_ip;
    uint16_t m_port;
    bool m_block;
};

} // namespace gengine::interface::network
