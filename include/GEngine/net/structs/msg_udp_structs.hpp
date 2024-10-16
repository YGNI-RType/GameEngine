/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** msg_udp_structs
*/

#pragma once

#include <cstdint>

namespace Network {

enum { CL_BROADCAST_PING, SV_BROADCAST_PING, CL_SENDCMD, SV_SNAPSHOT, CL_EVENT, CL_SV_FRAGMENT };

struct UDPSV_PingResponse {
    uint16_t tcpv4Port;
    uint16_t tcpv6Port;

    uint32_t maxPlayers;
    uint32_t currentPlayers;
};

struct UDPG_NetChannelHeader {
    uint64_t sequence;
    uint32_t ackFragmentSequence; /* the client will tell the amount of fragments he has received */

    /* optional, sending anyway */

    uint64_t ack = 0; /* m_udpInSequence */
};

/*********** Fragments ***********/

PACK(struct AUDPG_FragmentHeader {
    uint32_t
        idSequence; /* there might be multiple fragmentation at once (4 max), this number is incremented all time */
});

struct UDPG_MasterFragmentHeaderFrom {
    uint8_t nbHeaders; /* tells how many sequence header are there */
};

/* the one from is the one receiving the fragment, he hasn't asked for it ! */
PACK(struct UDPG_FragmentHeaderFrom
     : AUDPG_FragmentHeader {
         uint16_t receivedFragmentsMask; /* 0110 1100 */
                                         /* 0  : Want this Fragment */
                                         /* 1  : Ack this fragment */
     });

PACK(struct UDPG_FragmentHeaderTo {
    uint32_t idSequence;
    uint8_t fragId;    /* one fragment at a time */
    uint8_t fragIdMax; /* the number of fragments */
});

/*********************************/

} // namespace Network