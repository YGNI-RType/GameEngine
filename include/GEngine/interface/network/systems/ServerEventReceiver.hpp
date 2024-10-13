/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** ClientEvent.hpp
*/

#pragma once

#include "GEngine/interface/network/events/ClientEvent.hpp"
#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/net/net.hpp"

#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>

namespace gengine::interface::network::system {
class ServerClient {
public:
    ServerClient(std::shared_ptr<Network::NetClient> client)
        : m_client(client) {
    }

    std::shared_ptr<Network::NetClient> getNet(void) {
        return m_client;
    }
    bool shouldDelete(void) const {
        return m_shouldDelete;
    }
    void setShouldDelete(bool shouldDelete) {
        m_shouldDelete = shouldDelete;
    }

private:
    std::shared_ptr<Network::NetClient> m_client;

    bool m_shouldDelete = false;
};

template <class... Events>
class ServerEventReceiver : public System<ServerEventReceiver<Events...>> {
public:
    ServerEventReceiver()
        : m_server(Network::NET::getServer()) {
    }

    void init(void) override {
        this->template subscribeToEvent<gengine::system::event::StartEngine>(&ServerEventReceiver::onStartEngine);
        this->template subscribeToEvent<gengine::system::event::MainLoop>(&ServerEventReceiver::onMainLoop);
        (dynamicPublish<Events>(), ...);
    }

    void onStartEngine(gengine::system::event::StartEngine &e) {
        auto &eventManager = Network::NET::getEventManager();
        static std::uint64_t id = 0;

        static std::vector<Network::NetClient *> unwantedClients = {};

        eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
            Network::Event::CT_OnClientConnect, [this](std::shared_ptr<Network::NetClient> client) {
                std::lock_guard<std::mutex> lock(m_netMutex);

                if (std::find(unwantedClients.begin(), unwantedClients.end(), client.get()) != unwantedClients.end()) {
                    unwantedClients.erase(std::remove(unwantedClients.begin(), unwantedClients.end(), client.get()),
                                          unwantedClients.end());
                    return;
                }
                m_clients.push_back(std::make_pair(ServerClient(client), id));
                // TODO publish event
            });

        eventManager.registerCallback<Network::NetClient *>(
            Network::Event::CT_OnClientDisconnect, [this](Network::NetClient *client) {
                std::lock_guard<std::mutex> lock(m_netMutex);

                auto it = std::find_if(m_clients.begin(), m_clients.end(),
                                       [client](auto &pair) { return pair.first.getNet().get() == client; });
                if (it == m_clients.end()) {
                    unwantedClients.push_back(client);
                    return;
                }
                it->first.setShouldDelete(true);
            });
        id++;
    }

    void onMainLoop(gengine::system::event::MainLoop &e) {
        Network::UDPMessage msg(true, Network::CL_EVENT);
        size_t readCount = 0;
        for (auto &[client, id] : m_clients) {
            ServerClient &cli = client;
            if (client.shouldDelete()) { /* thread safe way of deleting a client from genengine */
                m_clients.erase(std::remove_if(m_clients.begin(), m_clients.end(),
                                               [&cli](auto &pair) { return pair.first.getNet() == cli.getNet(); }),
                                m_clients.end());
                continue;
            }
            if (!client.getNet()->popIncommingData(msg, readCount))
                continue;
            std::uint64_t nb;
            msg.readContinuousData(nb, readCount);

            for (int i = 0; i < nb; i++) {
                std::uint64_t type;
                msg.readContinuousData(type, readCount);
                auto it = m_eventsCallbacks.find(type);
                if (it == m_eventsCallbacks.end())
                    THROW_ERROR("here"); // TODO
                auto &[callback, size] = it->second;
                std::vector<Network::byte_t> data(size);

                msg.readData(data.data(), readCount, size);
                // std::cout << "size: " << size << std::endl;
                // std::cout << "data.data(): " << data.data() << std::endl;
                readCount += size;
                callback(data.data());
            }
        }
    }

private:
    template <typename T>
    void dynamicPublish(void) {
        m_eventsCallbacks.insert(std::make_pair(m_id, std::make_pair<std::function<void(void *)>, size_t>(
                                                        [this](void *data) -> void {
                                                            event::ClientEvent<T> event(*reinterpret_cast<T *>(data));
                                                            this->template publishEvent<event::ClientEvent<T>>(event);
                                                        },
                                                        sizeof(T))));
        m_id++;
    }
    std::uint64_t m_id = 0;
    const Network::NetServer &m_server;
    std::unordered_map<std::uint64_t, std::pair<std::function<void(void *)>, size_t>> m_eventsCallbacks;
    std::vector<std::pair<ServerClient, std::uint64_t>> m_clients;
    mutable std::mutex m_netMutex;
};

} // namespace gengine::interface::network::system
