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
#include "GEngine/interface/network/events/ClientEvent.hpp"

#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <mutex>

namespace gengine::interface::network::system {



    template <class... Events>
    class ServerEventReceiver: public System<ServerEventReceiver<Events...>> {
    public:
        ServerEventReceiver() :
                m_server(Network::NET::getServer())
        {
        }

        void init(void) override {
            this->template subscribeToEvent<gengine::system::event::StartEngine>(&ServerEventReceiver::onStartEngine);
            this->template subscribeToEvent<gengine::system::event::MainLoop>(&ServerEventReceiver::onMainLoop);
            (dynamicPublish<Events>(), ...);
        }

        void onStartEngine(gengine::system::event::StartEngine &e) {
            Network::NET::init();
            Network::NET::initServer();
            Network::NET::start();
            auto &eventManager = Network::NET::getEventManager();
            static std::uint64_t id = 0;

            eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
                Network::Event::CT_OnClientConnect, [this] (std::shared_ptr<Network::NetClient> client) {
                    std::lock_guard<std::mutex> lock(m_netMutex);
                    std::cout << "new client !" << std::endl;
                    m_clients.insert(std::make_pair(
                        client, id
                    ));
                    // TODO publish event
                }
            );

            eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
                Network::Event::CT_OnClientDisconnect, [this] (std::shared_ptr<Network::NetClient> client) {
                    std::lock_guard<std::mutex> lock(m_netMutex);
                    std::cout << "disconnect" << std::endl;

                    auto it = m_clients.find(client);

                    if (it == m_clients.end())
                        throw ""; // TODO
                    m_clients.erase(client);
                    // TODO publish event
                }
            );
            id++;
        }

        void onMainLoop(gengine::system::event::MainLoop &e) {
            // std::uint64_t howManyEvents;
            // size_t readOffset = 0;
            // msg.readContinuousData<std::uint64_t>(howManyEvents, readOffset);
            // for (std::uint64_t i = 0; i < howManyEvents; i++) {

            // }
            Network::UDPMessage msg(true, Network::CL_EVENT);
            size_t readCount = 0;
            for (auto &[client, id]: m_clients) {
                if (!client->popIncommingData(msg, readCount))
                    continue;
                std::uint64_t nb;
                msg.readContinuousData(nb, readCount);
                std::cout << "nb: " << nb << std::endl;

                for (int i = 0; i < nb; i++) {
                    std::uint64_t type;
                    msg.readContinuousData(type, readCount);
                    auto it = m_eventsCallbacks.find(type);
                    if (it == m_eventsCallbacks.end())
                        throw ""; // TODO
                    auto &[callback, size] = it->second;
                    std::vector<Network::byte_t> data(size);
                    msg.readData(data.data(), readCount, size);
                    readCount += size;
                    callback(data.data());
                }
            }
        }

    private:
        template <typename T>
        void dynamicPublish(void) {
            static std::uint64_t id = 0;
            m_eventsCallbacks.insert(std::make_pair(id,
                std::make_pair<std::function<void(void *)>, size_t>(
                    [this] (void *data) -> void {
                        event::ClientEvent<T> event(*reinterpret_cast<T*>(data));
                        this->template publishEvent<event::ClientEvent<T>>(event);
                    }, sizeof(T)
                )
                )
            );
            id++;
        }
        const Network::NetServer &m_server;
        std::unordered_map<std::uint64_t, std::pair<std::function<void(void *)>, size_t>> m_eventsCallbacks;
        std::unordered_map<std::shared_ptr<Network::NetClient>, std::uint64_t> m_clients;
        mutable std::mutex m_netMutex;
    };

} // namespace gengine::interface::network::system
