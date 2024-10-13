/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_client
*/

#pragma once

#include "events/socket_event.hpp"
#include "net_channel.hpp"
#include "net_queue.hpp"

#include <memory>
#include <string>
#include <vector>

namespace Network {

#define MAX_SZ_NAME 64
#define PACKET_BACKUP 32

/*
this info is transmitted to network, WE NEED TO USE C ARRAYS
this is global TO ALL TYPE OF GAMES, we need to set custom data information one day
*/
class NetClientInfo {
public:
    NetClientInfo() = default;
    ~NetClientInfo() = default;

    void setName(const std::string &name);
    const std::string &getName(void) const;

private:
    char m_name[MAX_SZ_NAME];

    uint16_t rate;             /* rate of requests, if lan don't care */
    uint16_t snapshotRate;     /* rate of sending snapshots (msec) */
    bool transmitHighFreqData; /* voip, webcam feed etc...*/
};

/* Since the engine and the snapshots are not defined in advance, we store them in heap with a predefined size */
class NetClientSnapshot {
public:
    NetClientSnapshot(size_t size);
    ~NetClientSnapshot() = default;

private:
    std::vector<byte_t> m_data;
};

/* likely composed */
class NetClient {

public:
    NetClient(std::unique_ptr<Address> addr, SocketTCP &&socket, SocketUDP &socketudp, Event::SocketEvent &socketEvent);
    ~NetClient() = default;

    NetChannel &getChannel(void) {
        return m_channel;
    }

    SocketUDP &getSocketUdp(void) {
        return m_socketUdp;
    }

    bool isDisconnected(void) const {
        return m_channel.isDisconnected();
    }

    bool handleTCPEvents(fd_set &readSet);
    bool handleClientStream(void);
    bool handleClientDatagram(UDPMessage &msg);

public:
    bool sendPackets(void);
    bool sendDatagram(UDPMessage &msg);
    void sendStream(const TCPMessage &msg);

public:
    /** Net Queue **/

    bool pushData(const UDPMessage &msg, bool shouldAck);
    bool popIncommingData(UDPMessage &msg, size_t &readCount);
    size_t getSizeIncommingData(void) const {
        return m_packInData.size();
    }

private:
    bool retrieveWantedOutgoingData(UDPMessage &msg, size_t &readCount);
    bool retrieveWantedOutgoingDataAck(UDPMessage &msg, size_t &readCount);
    bool pushIncommingData(const UDPMessage &msg, size_t readCount);

private:
    NetChannel m_channel;
    NetClientInfo m_info;

    int m_challenge = -1; /* challenge for authoring / avoid ddos */
    clientState m_state = CS_FREE;
    connectionState m_connectionState = CON_UNINITIALIZED;

    /* todo : change based on average size */
    NetQueue<16, 160> m_packInData;      /* todo : get the size of Usercmd + own voip / */
    NetQueue<32, 1400> m_packOutData;    /* voiceip etc.. */
    NetQueue<24, 5000> m_packOutDataAck; /* snapshot */

    // NetClientSnapshot m_snapshots[PACKET_BACKUP];

    /* sends CMD, not any data */

    SocketUDP &m_socketUdp;

    uint16_t ping = 0;

    size_t m_maxRate = 0;
};
} // namespace Network
