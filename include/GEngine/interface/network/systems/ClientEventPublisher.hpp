/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** ClientEvent.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/net/net.hpp"
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <memory>

namespace gengine::interface::network::system {

    template <class... Events>
    class ClientEventPublisher: public System<ClientEventPublisher<Events...>> {
    public:
        ClientEventPublisher() :
                m_client(Network::NET::getClient()),
                m_msg(true, Network::CL_EVENT)
        {
            // Network::NET::init();
            // Network::NET::initClient();
        }

        void init(void) override {
            this->template subscribeToEvent<gengine::system::event::StartEngine>(&ClientEventPublisher::onStartEngine);
            this->template subscribeToEvent<gengine::system::event::MainLoop>(&ClientEventPublisher::onMainLoop);
            (dynamicSubscribe<Events>(), ...);
        }

        void onStartEngine(gengine::system::event::StartEngine &e) {
            // Network::NET::start();
            // auto &eventManager = Network::NET::getEventManager();

            // eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
            //     Network::Event::CT_OnClientConnect, [this] (std::shared_ptr<Network::NetClient> client) {
            //         std::cout << "new client !" << std::endl;
            //     }
            // );
            m_msg.setAck(true);
            m_msg.appendData<std::uint64_t>(0);
            m_eventCount = 0;
        }

        void onMainLoop(gengine::system::event::MainLoop &e) {
            m_msg.writeData(m_eventCount, sizeof(Network::UDPG_NetChannelHeader), false);
            m_client.pushData(m_msg);
            m_msg.clear();
            m_msg.appendData<std::uint64_t>(42);
            m_eventCount = 0;
        }

    private:
        template <typename T>
        void dynamicSubscribe(void) {
            static std::uint64_t id = 0;
            m_events.insert(std::make_pair(
                std::type_index(typeid(T)),
                id)
            );
            this->template subscribeToEvent<T>(
                [this] (T &event) -> void {
                    std::cout << "event" << std::endl;
                    m_msg.appendData<std::size_t>(id);
                    m_msg.appendData<T>(event);
                    m_eventCount++;
                }
            );
            id++;
        }

        Network::UDPMessage m_msg;
        std::uint64_t m_eventCount = 0;
        Network::CLNetClient &m_client;
        std::unordered_map<std::type_index, std::uint64_t> m_events;
    };

} // namespace gengine::interface::network::system
