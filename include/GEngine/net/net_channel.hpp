/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_channel
*/

#pragma once

#include "net_msg.hpp"
#include "net_socket.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

// UN udp message / tcp message ne doit pas être envoyé brut,
// il doit être envoyé à travers une pool, qui en fonction du ratelimit enverront tout ça
// Un classe de message spécialisé, donc avec les headers mêem du udp message qui sotn store dans un gros buffer, dont
// les seuls traces sont des structs, précisant leur segmentation.
// la taille du buffer est réplique pour MAXCLIENTS, dans un convar CMD cappé à 100 jouers

#define MAX_CONCURRENT_FRAGMENTS 3
#define FRAG_SEQUENCE_TABLE_SZ sizeof(uint16_t) * 8

#define UDP_POOL_SZ MAX_UDP_PACKET_LENGTH *FRAG_SEQUENCE_TABLE_SZ *MAX_CONCURRENT_FRAGMENTS
#define TCP_POOL_SZ MAX_TCP_MSGLEN

#define NETCHAN_GENCHECKSUM(challenge, sequence) ((challenge) ^ ((sequence) * (challenge)))

namespace Network {

typedef enum {
    CS_FREE,      // can be reused for a new connection
    CS_ZOMBIE,    // client has been disconnected, but don't reuse
                  // connection for a couple seconds
    CS_CONNECTED, // has been assigned to a client_t, but no gamestate yet
    CS_PRIMED,    // gamestate has been sent, but client hasn't sent a usercmd
    CS_ACTIVE     // client is fully in game
} clientState;

typedef enum {
    CON_UNINITIALIZED,
    CON_DISCONNECTED, // not talking to a server
    CON_AUTHORIZING,  // not used any more, was checking cd key
    CON_CONNECTING,   // sending request packets to the server
    CON_CHALLENGING,  // sending challenge packets to the server
    CON_CONNECTED,    // netchan_t established, getting gamestate
    CON_LOADING,      // only during cgame initialization, never during main loop
    CON_PRIMED,       // got gamestate, waiting for first frame
    CON_ACTIVE,       // game views should be displayed
    CON_CINEMATIC     // playing a cinematic or a static pic, not connected to a server
} connectionState;

class PacketPoolUdp {

    static const size_t CHUNK_SIZE =
        MAX_UDP_PACKET_LENGTH - sizeof(UDPG_FragmentHeaderTo) - sizeof(UDPG_NetChannelHeader);

public:
    typedef std::array<byte_t, CHUNK_SIZE> chunk_t;

private:
    /* type, flag, numbers of chunk, last chunk size, cur mask, pool offset */
    using poolSequence_t = std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, size_t>;

public:
    PacketPoolUdp() = default;
    ~PacketPoolUdp() = default;

    /* send */

    bool addMessage(uint32_t sequence, const UDPMessage &msg);
    std::vector<const chunk_t *> getMissingFragments(uint32_t sequence, uint16_t mask);
    void constructMessage(UDPMessage &msg, const chunk_t *chunk, size_t chunk_size,
                          const UDPG_FragmentHeaderTo &header);

    /* recv */

    bool recvMessage(const UDPMessage &msg, size_t &readOffset, uint32_t &fragSequence);
    std::pair<uint32_t, uint16_t> getCurrentSequence(void);
    uint16_t getMask(uint32_t sequence);
    void reconstructMessage(uint32_t sequence, UDPMessage &msg);

    bool deleteSequence(uint32_t sequence);

    poolSequence_t getMsgSequenceInfo(uint32_t sequence) const {
        return m_poolSequences.at(sequence);
    }
    bool receivedFullSequence(uint32_t sequence);
    size_t getPoolSize(void) const {
        return m_poolSequences.size();
    }

private:
    std::unordered_map<uint32_t, poolSequence_t> m_poolSequences;
    std::vector<chunk_t> m_pool; /* pool of packet, just send it straight away, no modifications (header are btw)*/
};

/*
    server : used for each NetClient
    client : used only to send cmd in server
*/
class NetChannel {
public:
    // NetChannel() = default;
    NetChannel(bool isServer, std::unique_ptr<Address> addr, SocketTCP &&socket);
    NetChannel(const NetChannel &other) = delete;
    NetChannel &operator=(const NetChannel &other) = delete;
    NetChannel(NetChannel &&other) = default;
    NetChannel &operator=(NetChannel &&other) = default;
    ~NetChannel() = default;

    const Address &getAddressTCP(void) const {
        return *m_toTCPAddress;
    }
    const Address &getAddressUDP(void) const {
        return *m_toUDPAddress;
    }

    bool isEnabled(void) const {
        return m_enabled;
    }
    bool isDisconnected(void) const {
        return m_disconnect;
    }

    uint64_t getLastACKPacketId(void) const {
        return m_udpACKClientLastACK;
    }

    const SocketTCP &getTcpSocket(void) const {
        return m_tcpSocket;
    }
    void setTcpSocket(SocketTCP &&socket) {
        m_tcpSocket = std::move(socket);
    }

    uint32_t getChallenge(void) const {
        return m_challenge;
    }
    void setChallenge(int challenge) {
        m_challenge = challenge;
    }
    bool canCommunicate(void) {
        return m_enabled && m_tcpSocket.getSocket() != -1;
    }

    void createUdpAddress(uint16_t udpport);
    bool readDatagram(SocketUDP &socket, UDPMessage &msg, size_t &readOffset);
    /* steam if proper to socket, taht's why msg in not const */
    bool readStream(TCPMessage &msg);

public:
    bool sendDatagram(SocketUDP &socket, UDPMessage &msg);
    bool sendStream(const TCPMessage &msg);

private:
    bool sendDatagrams(SocketUDP &socket, uint32_t sequence,
                       const std::vector<const Network::PacketPoolUdp::chunk_t *> &vec);

public:
    bool isTimeout(void) const;

private:
    bool m_enabled = false;
    bool m_disconnect = false;

    std::unique_ptr<Address> m_toTCPAddress; /* the recast to v6 or v4 is done later */
    std::unique_ptr<Address> m_toUDPAddress; /* the recast to v6 or v4 is done later */

    /* UDP */

    /* TODO : add delay (?) */
    // PacketPoolUdp m_udpPoolUnsent;

    uint32_t m_challenge = -1;

    /* most likely fragments, since the packets may be too big (mostly (always) for client from server) */
    PacketPoolUdp m_udpPoolSend;
    PacketPoolUdp m_udpPoolRecv;

    uint32_t m_droppedPackets = 0;

    /* don't give a shit if the packet went through : voip / camera */
    uint64_t m_udpInSequence = 0;
    uint64_t m_udpOutSequence = 1;

    /* snapshot, needs client acknowledge to do some things */
    uint64_t m_udpACKInSequence = 0;
    uint64_t m_udpACKOutSequence = 1;
    uint64_t m_udpACKClientLastACK = 0;

    uint64_t m_udplastsent = 0;
    uint64_t m_udplastrecv = 0;
    size_t m_udplastsentsize = 0;

    uint32_t m_udpMyFragSequence = 0;
    uint32_t m_udpFromFragSequence = 0;
    uint8_t m_udpNbFragSequence = 0; /* number of existing frag sequences */

    /*******/

    /* TCP */

    SocketTCP m_tcpSocket;
    /* unsent data (mostly rather small data, downloads are another story)*/
    // PacketPoolTcp m_tcpPool;

    /*******/
};
} // namespace Network
