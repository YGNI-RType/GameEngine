/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_client
*/

#pragma once

#include "net_channel.hpp"

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
    NetClient(std::unique_ptr<Address> addr, SocketTCP &&socket, SocketUDP &socketudp);
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

    void sendDatagram(UDPMessage &msg);
    void recvDatagram(UDPMessage &msg);

    bool handleTCPEvents(fd_set &readSet);
    bool handleClientMsg(void);
    void sendStream(const TCPMessage &msg);

private:
    NetChannel m_channel;
    NetClientInfo m_info;

    int m_challenge = -1; /* challenge for authoring / avoid ddos */
    clientState m_state = CS_FREE;
    connectionState m_connectionState = CON_UNINITIALIZED;

    // NetClientSnapshot m_snapshots[PACKET_BACKUP];

    /* sends CMD, not any data */

    SocketUDP &m_socketUdp;

    uint16_t ping;
};
} // namespace Network
