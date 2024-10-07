/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_client_voip
*/

#pragma once

#include "net_common.hpp"

#include <vector>

namespace Network {

#define VOIP_QUEUE_LENGTH 64
#define VOIP_PACKET_SIZE 4000

typedef struct voipServerPacket_s {
    uint32_t generation;
    uint32_t sequence;
    uint32_t frames;
    uint32_t len;
    uint32_t sender;
    int flags;
    byte_t data[VOIP_PACKET_SIZE];
} voipServerPacket_t;

class NetClientVoip {

public:
    NetClientVoip();
    ~NetClientVoip();

    void sendVoipPacket(const voipServerPacket_t &packet);
    voipServerPacket_t getVoipPacket(void);

private:
    bool hasVoip;
    bool muteAllVoip;
    bool ignoreVoipFromClient[MAX_CLIENTS];

    std::vector<voipServerPacket_t> voipPacket; //[VOIP_QUEUE_LENGTH];
    int queuedVoipPackets;
    int queuedVoipIndex;
};
} // namespace Network
