/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event
*/

#pragma once

#include "events/socket_event.hpp"

#include <any>
#include <functional>
#include <memory>
#include <queue>
#include <thread>
#include <typeindex>

namespace Network::Event {
enum Type { CONNECT, DISCONNECT, SEND_QUEUED_PACKET, PING };

enum CallbackType { CT_OnClientConnect, CT_OnClientDisconnect, CT_OnServerConnect, CT_OnServerDisconnect };

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

    /* game engine thread */
    template <typename T>
    void addEvent(Type type, const T &data) {
        std::unique_ptr<Info<T>> info = std::make_unique<Info<T>>();

        info->type = type;
        info->data = std::make_unique<T>(data);
        storeEvent(std::move(info));
        m_socketEvent.signal();
    }

    void createSets(fd_set &readSet);
    bool handleEvent(fd_set &readSet);

    void storeEvent(std::unique_ptr<InfoHeader> info);
    void sendPackets(void);

    SocketEvent &getSocketEvent() { return m_socketEvent; }

    /** callback **/

    using CallbackMap = std::unordered_map<CallbackType, std::vector<std::pair<std::type_index, std::any>>>;

    template <typename T>
    void registerCallback(const CallbackType &type, std::function<void(T)> callback) {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_callbacks[type].emplace_back(std::type_index(typeid(T)), callback);
    }

    // Function to invoke callbacks with any argument type
    template <typename T>
    void invokeCallbacks(const CallbackType &type, T arg) {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_callbacks.find(type) == m_callbacks.end())
            return;

        for (const auto &callbackPair : m_callbacks.at(type)) {
            if (callbackPair.first != std::type_index(typeid(T)))
                continue;

            auto callbackAny = std::any_cast<std::function<void(T)>>(callbackPair.second);
            std::thread([callbackAny, arg]() { callbackAny(arg); }).detach();
        }
    }

private:
    void handleNewEngineReq(InfoHeader &header);

    SocketEvent m_socketEvent;

    mutable std::mutex m_mutex;
    std::queue<std::unique_ptr<InfoHeader>> m_events;
    CallbackMap m_callbacks;
};
} // namespace Network::Event
