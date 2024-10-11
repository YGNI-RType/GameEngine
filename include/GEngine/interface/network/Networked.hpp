#pragma once

#include "GEngine/driver/Engine.hpp"
#include "GEngine/game/Engine.hpp"
#include "GEngine/interface/Base.hpp"
#include "GEngine/interface/network/systems/Snapshot.hpp"
#include "GEngine/libdev/systems/MainLoop.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/interface/network/systems/ServerEvent.hpp"

#include "GEngine/net/msg.hpp"
#include "GEngine/net/net.hpp"
#include "GEngine/net/structs/msg_udp_structs.hpp"

#include <functional>
#include <unordered_map>
#include <type_traits>
#include <typeindex>
#include <iostream>
#include <memory>

namespace gengine::interface::network {

class Networked : public Base {
public:
    template <typename... Events>
    Networked(driver::Engine &driverEngine, game::Engine &gameEngine, const std::string &ip = "", uint16_t port = 0,
              bool block = false, Events... events)
        : m_gameEngine(gameEngine)
        , m_driverEngine(driverEngine)
        , m_ip(ip)
        , m_port(port)
        , m_block(block)
#ifdef Server
        , m_server(Network::NET::getServer())
#else
        , m_msg(true, Network::CL_EVENT)
        , m_client(Network::NET::getClient())
#endif
    {
        Network::NET::init();

#ifdef Server
        std::cout << "server starting..." << std::endl;
        Network::NET::initServer();
        Network::NET::start();
        m_gameEngine.registerSystem<gengine::interface::network::system::ServerEvent>();
#else
        std::cout << "client starting..." << std::endl;
        Network::NET::initClient();
        Network::NET::start();
        std::cout << m_client.connectToServer(ip, port, block) << std::endl;


        m_driverEngine.subscribeCallback<gengine::system::event::StartEngine>(
            [this] (gengine::system::event::StartEngine &) -> void {
                m_msg.setAck(true);
                m_msg.appendData<std::size_t>(0);
                m_eventCount = 0;
            }
        );

        m_driverEngine.subscribeCallback<gengine::system::event::MainLoop>(
            [this] (gengine::system::event::MainLoop &) -> void {
                m_msg.writeData(m_eventCount, sizeof(std::uint64_t), false);
                m_client.pushData(m_msg);
                m_msg.clear();
                m_msg.appendData<std::size_t>(0);
                m_eventCount = 0;

                // temp
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        );
#endif
        m_gameEngine.registerSystem<system::Snapshot>(gameEngine.getWorld());

        getInstance(this);
        if constexpr (sizeof...(Events) > 0) {
            registerEvents<Events...>();
        }

        m_driverEngine.registerSystem<gengine::system::AutoMainLoop>(); // force registration of autoMainloop System
        m_gameEngine.registerSystem<gengine::system::AutoMainLoop>();   // force registration of autoMainloop System
    }

    ~Networked() {
        Network::NET::stop();
    }

#ifdef Server
    void run() override {
        m_gameEngine.start();
        m_gameEngine.compute();
    }

    template <typename T>
    void registerEvent() {
        static std::uint64_t id = 0;
        m_eventsCallbacks.insert(std::make_pair(id, [this](const Network::UDPMessage &msg, std::size_t readOffset) -> void {
            // T event;
            // msg.readContinuousData<T>(event, readOffset);
            // m_gameEngine.publishEvent(event);
        }));
        id++;
    }
#else
    void run() override {
        m_driverEngine.start();
        m_driverEngine.compute();
    }

    template <typename T>
    void registerEvent() {
        static std::uint64_t id = 0;
        m_events.insert(std::make_pair(std::type_index(typeid(T)), id));
        m_driverEngine.subscribeCallback<T>([this](gengine::Event &e) -> void {
            m_msg.appendData<std::size_t>(id);
            m_msg.appendData<T>(e);
            m_eventCount++;
        });
        id++;
    }
#endif

    static Networked *getInstance(Networked *i) {
        static Networked *_i = nullptr;

        if (i)
            _i = i;
        return _i;
    }

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

    std::unordered_map<std::uint64_t, std::function<void(const Network::UDPMessage &, std::size_t)>> m_eventsCallbacks;
    std::unordered_map<std::type_index, std::uint64_t> m_events;
#ifdef Server
    const Network::NetServer &m_server;
#else
    Network::UDPMessage m_msg;
    Network::CLNetClient &m_client;
    std::uint64_t m_eventCount;
#endif

    template <typename T, typename... Rest>
    void registerEvents() {
        registerEvent<T>();
        if constexpr (sizeof...(Rest) > 0) {
            registerEvents<Rest...>();
        }
    }

};

} // namespace gengine::interface::network
