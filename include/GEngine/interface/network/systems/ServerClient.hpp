/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** ServerClient.hpp
*/

#pragma once

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