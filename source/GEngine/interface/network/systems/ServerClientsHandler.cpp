/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** ServerClientsHandler.cpp
*/

#include "GEngine/interface/network/systems/ServerClient.hpp"

#include "GEngine/interface/events/RemoteDriver.hpp"
#include "GEngine/net/msg.hpp"
#include "GEngine/net/net.hpp"
#include "GEngine/net/net_client.hpp"

namespace gengine::interface::network::system {
ServerClient::ServerClient(std::shared_ptr<Network::NetClient> client)
    : m_client(client) {
}

std::shared_ptr<Network::NetClient> ServerClient::getNet(void) const {
    return m_client;
}

ServerClientsHandler::ServerClientsHandler() {
}

void ServerClientsHandler::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&ServerClientsHandler::onStartEngine);
    subscribeToEvent<gengine::system::event::MainLoop>(&ServerClientsHandler::onMainLoop);
}

void ServerClientsHandler::onStartEngine(gengine::system::event::StartEngine &e) {
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

            gengine::interface::component::RemoteDriver newRemoteDriver;
            m_clients.insert({newRemoteDriver, client});
            publishEvent<gengine::interface::event::NewRemoteDriver>(
                gengine::interface::event::NewRemoteDriver(newRemoteDriver));
        });

    eventManager.registerCallback<Network::NetClient *>(
        Network::Event::CT_OnClientReady, [this](Network::NetClient *client) {
            std::lock_guard<std::mutex> lock(m_netMutex);
            auto it = std::find_if(m_clients.begin(), m_clients.end(),
                                   [client](const auto &pair) { return pair.second.getNet().get() == client; });
            if (it == m_clients.end())
                return; // for some reason, client doesn't exist ???

            it->second.setReady(true);
        });

    eventManager.registerCallback<Network::NetClient *>(
        Network::Event::CT_OnClientDisconnect, [this](Network::NetClient *client) {
            std::lock_guard<std::mutex> lock(m_netMutex);

            auto it = std::find_if(m_clients.begin(), m_clients.end(),
                                   [client](auto &pair) { return pair.second.getClient().get() == client; });
            if (it == m_clients.end()) {
                unwantedClients.push_back(client);
                return;
            }
            it->second.setShouldDelete(true);

            publishEvent<gengine::interface::event::DeleteRemoteDriver>(
                gengine::interface::event::DeleteRemoteDriver(it->first));
        });
}

void ServerClientsHandler::onMainLoop(gengine::system::event::MainLoop &e) {
    std::lock_guard<std::mutex> lock(m_netMutex);

    for (auto it = m_clients.begin(); it != m_clients.end();)
        if (it->second.shouldDelete())
            it = m_clients.erase(it);
        else
            ++it;
}
} // namespace gengine::interface::network::system