/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event
*/

#include "GEngine/net/net_event.hpp"
#include "GEngine/net/events/connection.hpp"
#include "GEngine/net/net.hpp"

namespace Network::Event {
void Manager::createSets(fd_set &readSet) {
    m_socketEvent.setFdSet(readSet);
}

bool Manager::handleEvent(fd_set &readSet) {
    if (!m_socketEvent.isFdSet(readSet))
        return false;

    m_socketEvent.wait();
    while (true) {
        std::unique_ptr<InfoHeader> info;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_events.empty())
                return true;
            info = std::move(m_events.front());
            m_events.pop();
        }

        handleNewEngineReq(*info);
    }
}

void Manager::storeEvent(std::unique_ptr<InfoHeader> info) {
    std::lock_guard<std::mutex> lock(m_mutex);

    m_events.push(std::move(info));
}

void Manager::handleNewEngineReq(InfoHeader &header) {
    switch (header.type) {
    case CONNECT: {
        auto &client = NET::getClient();
        auto &dataPtr = reinterpret_cast<Info<ConnectInfo> &>(header).data;

        if (dataPtr->pingIndex != -1) /* this means they found it via pinging LAN */
            client.connectToServer(dataPtr->pingIndex);
        else
            client.connectToServer(dataPtr->ip, dataPtr->port);
    } break;
    case DISCONNECT: {
        auto &client = NET::getClient();

        client.disconnectFromServer();
    } break;
    case SEND_QUEUED_PACKET: /* send a tcp message */
        sendPackets();
        break;
    case PING:
        NET::pingServers();
        break;
    default:
        break;
    }
}

void Manager::sendPackets(void) {
    NetServer &server = NET::getServer();
    if (!server.sendPackets())
        return;

    CLNetClient &client = NET::getClient();
    if (!client.sendPackets())
        return;
}
} // namespace Network::Event