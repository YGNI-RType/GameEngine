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
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
            m_msg.writeData(m_eventCount, sizeof(Network::UDPG_NetChannelHeader), 0, false);
            std::cout << "event count: " << m_eventCount << std::endl;
            m_client.pushData(m_msg);
            m_msg.clear(true);

            // Thomas : ça va toujours crash tant que la main loop n'aura pas confirmation du "Server Ready", d'où la wait de 2 secondes
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
                    // std::cout << "event" << std::endl;
                    m_msg.appendData<std::size_t>(id);
                    m_msg.appendData<T>(event);
                    m_eventCount++;

                    // temp but PLEASE IN THE FUTURE ADD A CLOCK
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
