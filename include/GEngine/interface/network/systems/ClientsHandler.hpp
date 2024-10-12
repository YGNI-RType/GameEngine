// /*
// ** EPITECH PROJECT, 2024
// ** GameEngine
// ** File description:
// ** ClientsHandler.hpp
// */

// #pragma once

// #include "GEngine/libdev/System.hpp"
// #include "GEngine/libdev/systems/events/MainLoop.hpp"
// #include "GEngine/libdev/systems/events/Native.hpp"
// #include "GEngine/net/net.hpp"
// #include <iostream>
// #include <memory>
// #include <typeindex>
// #include <unordered_map>

// namespace gengine::interface::network::system {
// class ServerClient {
// public:
//     ServerClient(std::shared_ptr<Network::NetClient> client, uint64_t firsSnapshotId);

//     std::shared_ptr<Network::NetClient> getNet(void) const;

//     uint64_t getLastAck(void) const {
//         return m_lastAck;
//     }
//     void setLastAck(uint64_t lastAck) {
//         m_lastAck = lastAck;
//     }

//     uint64_t getSnapshotId(void) const {
//         return m_firsSnapshotId;
//     }
//     void setSnapshotId(uint64_t id) {
//         m_firsSnapshotId = id;
//     }

//     bool shouldDelete(void) const {
//         return m_shouldDelete;
//     }
//     void setShouldDelete(bool shouldDelete) {
//         m_shouldDelete = shouldDelete;
//     }

// private:
//     std::shared_ptr<Network::NetClient> m_client;
//     uint64_t m_firsSnapshotId;

//     uint64_t m_lastAck = 0;
//     bool m_shouldDelete = false;
// };

// template <class... Events>
// class ServerClientsHandler : public System<Clients<Events...>> {
// public:
//     ServerClientsHandler(){
//     }

//     void init(void) override {

//     }

//     void onStartEngine(gengine::system::event::StartEngine &e) {
//         auto &eventManager = Network::NET::getEventManager();

//     /* Imagine for some reason (most likely impossible) we receive the event of deleting before creating. that's
//      * embarrassing */
//     static std::vector<Network::NetClient *> unwantedClients = {};

//     eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
//         Network::Event::CT_OnClientConnect, [this](std::shared_ptr<Network::NetClient> client) {
//             std::lock_guard<std::mutex> lock(m_netMutex);

//             if (std::find(unwantedClients.begin(), unwantedClients.end(), client.get()) != unwantedClients.end()) {
//                 unwantedClients.erase(std::remove(unwantedClients.begin(), unwantedClients.end(), client.get()),
//                                       unwantedClients.end());
//                 return;
//             }
//             publishEvent
//         });
//     eventManager.registerCallback<Network::NetClient *>(
//         Network::Event::CT_OnClientDisconnect, [this](Network::NetClient *client) {
//             std::lock_guard<std::mutex> lock(m_netMutex);

//             auto it = std::find_if(m_clientSnapshots.begin(), m_clientSnapshots.end(),
//                                    [client](const auto &pair) { return pair.first.getNet().get() == client; });
//             if (it == m_clientSnapshots.end()) {
//                 unwantedClients.push_back(client);
//                 return;
//             }
//             it->first.setShouldDelete(true);
//         });
//     }

//     void onMainLoop(gengine::system::event::MainLoop &e) {
//     }

// private:
//     std::vector<SnapshotClient> m_clients;

//     mutable std::mutex m_netMutex;
// };

// } // namespace gengine::interface::network::system
