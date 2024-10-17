/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** cl_net_client
*/

#pragma once

#include "net_channel.hpp"
#include "net_common.hpp"
#include "net_queue.hpp"

#include <memory>
#include <vector>

namespace Network {

struct PingResponse {
    UDPSV_PingResponse response;
    std::unique_ptr<Address> addr;
};

class CLNetClient {

public:
    CLNetClient(SocketUDP &socketUdp, AddressType type, Event::SocketEvent &socketEvent)
        : m_socketUdp(socketUdp)
        , m_addrType(type)
        , m_netChannel(NetChannel(false, nullptr, SocketTCP()))
        , m_packOutData(socketEvent)
        , m_packInData(socketEvent)
        , m_packInDataAck(socketEvent) {};
    ~CLNetClient() = default;

    void init(void);
    void stop(void);

    /* index of the pinged servers */
    bool connectToServer(size_t index);
    bool connectToServer(const std::string &ip, uint16_t port, bool block = false);
    void disconnectFromServer(void);

    void createSets(fd_set &readSet);

    bool handleTCPEvents(fd_set &readSet);
    bool handleUDPEvents(SocketUDP &socket, UDPMessage &msg, const Address &addr);

    bool handleServerUDP(SocketUDP &socket, UDPMessage &msg, const Address &addr);
    bool handleServerTCP(const TCPMessage &msg);

    void setChallenge(int challenge) {
        m_challenge = challenge;
    }
    int getChallenge(void) const {
        return m_challenge;
    }

    auto &getPingResponses(void) const {
        return m_pingedServers;
    }

    bool isConnected(void) const {
        return m_connectionState >= CON_AUTHORIZING;
    }

public:
    bool sendPackets(void);
    bool sendDatagram(UDPMessage &finishedMsg);

public:
    void pingLanServers(void);
    void getPingResponse(const UDPMessage &msg, const Address &addr);

public:
    /** Net Queue **/

    bool pushData(const UDPMessage &msg);
    bool popIncommingData(UDPMessage &msg, size_t &readCount, bool shouldAck);
    size_t getSizeIncommingData(bool ack) const {
        if (ack)
            return m_packInDataAck.size();
        return m_packInData.size();
    }
    size_t getSizeIncommingData(uint8_t type, bool ack) const {
        if (ack)
            return m_packInDataAck.size(type);
        return m_packInData.size(type);
    }

private:
    bool retrieveWantedOutgoingData(UDPMessage &msg, size_t &readCount);
    bool pushIncommingData(const UDPMessage &msg, size_t readCount);
    bool pushIncommingDataAck(const UDPMessage &msg, size_t readCount);

    int m_challenge = -1;

    bool m_enabled = false;
    clientState m_state = CS_FREE;
    connectionState m_connectionState = CON_UNINITIALIZED;

    /* todo : change based on average size */
    NetQueue<24, 160> m_packOutData;    /* todo : get the size of Usercmd + own voip / */
    NetQueue<32, 1400> m_packInData;    /* voiceip etc.. */
    NetQueue<60, 15000> m_packInDataAck; /* snapshot */

    SocketUDP &m_socketUdp;
    AddressType m_addrType;

    NetChannel m_netChannel;
    std::vector<PingResponse> m_pingedServers;

    /* in bytes from data (header do not count), can be updated via cvar */
    size_t m_maxRate = 10000;
};
} // namespace Network
