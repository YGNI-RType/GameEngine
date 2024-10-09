/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event
*/

#pragma once

#include "events/socket_event.hpp"

#include <memory>
#include <queue>
#include <thread>

namespace Network::Event {
enum Type { CONNECT, DISCONNECT, SEND_QUEUED_PACKET, PING };

struct InfoHeader {
    Type type;
};

template <typename T>
struct Info : public InfoHeader {
    std::unique_ptr<T> data;
};

class Manager {
public:
    Manager() = default;
    ~Manager() = default;

    template <typename T>
    void addEvent(Type type, const T &data) {
        Info<T> info;

        info.type = type;
        info.data = std::make_unique<T>(data);
        storeEvent(std::make_unique<InfoHeader>(info));
    }

    void createSets(fd_set &readSet);
    bool handleEvent(fd_set &readSet);

    void storeEvent(std::unique_ptr<InfoHeader> info);
    void sendPackets(void);

private:
    void handleNewEngineReq(InfoHeader &header);

    SocketEvent m_socketEvent;

    mutable std::mutex m_mutex;
    std::queue<std::unique_ptr<InfoHeader>> m_events;
};
} // namespace Network::Event
