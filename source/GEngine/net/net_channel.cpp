/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_channel
*/

#include "GEngine/net/net_channel.hpp"
#include "GEngine/cvar/net.hpp"
#include "GEngine/net/net_socket_error.hpp"
#include "GEngine/time/time.hpp"

#include <iostream>

namespace Network {

NetChannel::NetChannel(bool isServer, std::unique_ptr<Address> clientAddress, SocketTCP &&socket)
    : m_enabled(true)
    , m_toTCPAddress(std::move(clientAddress))
    , m_tcpSocket(std::move(socket)) {
    if (!isServer)
        return;

    /* each has challenge, avoid packet hi-jacking (todo (?) challenge are used for ddos, but is that the system
     * preventing it instead of us ?) */
    m_challenge = (((unsigned int)rand() << 16) ^ (unsigned int)rand()) ^ Time::Clock::milliseconds();
}

void NetChannel::createUdpAddress(uint16_t udpport) {
    if (m_toTCPAddress->getType() == AT_IPV6) {
        auto ipv6 = static_cast<AddressV6 *>(m_toTCPAddress.get());
        m_toUDPAddress = std::make_unique<AddressV6>(AT_IPV6, udpport, ipv6->getAddress(), ipv6->getScopeId());
    } else
        m_toUDPAddress =
            std::make_unique<AddressV4>(AT_IPV4, udpport, static_cast<AddressV4 *>(m_toTCPAddress.get())->getAddress());
}

bool NetChannel::sendDatagrams(SocketUDP &socket, uint32_t sequence,
                               const std::vector<const Network::PacketPoolUdp::chunk_t *> &fragments) {
    auto [msgType, flags, maxSize, lastChunkSz, _mask, _] = m_udpPoolSend.getMsgSequenceInfo(sequence);
    uint8_t i = 0;

    /* todo : add rate limit and all, only do it once though */
    for (const auto &chunk : fragments) {
        UDPMessage newMsg(true, msgType);
        newMsg.setFlag(flags);
        newMsg.setFragmented(true);

        UDPG_FragmentHeaderTo fragHeader;
        fragHeader.idSequence = sequence;
        fragHeader.fragId = i;
        fragHeader.fragIdMax = maxSize;

        m_udpPoolSend.constructMessage(newMsg, chunk, fragments.back() == chunk ? lastChunkSz : chunk->size(),
                                       fragHeader);

        // std::cout << "(" << sequence << ") Sending fragment: " << (int)i << " | " << newMsg.getSize() << " H: " << newMsg.getHash() << std::endl;
        sendDatagram(socket, newMsg);
        i++;
    }
    return true;
}

bool NetChannel::sendDatagram(SocketUDP &socket, UDPMessage &msg) {
    if (!m_enabled || m_toUDPAddress == nullptr)
        return false;

    size_t msgLen = msg.getSize();

    /* check the client rating before or after ? */

    uint64_t &udpOutSequence = msg.shouldAck() ? m_udpACKOutSequence : m_udpOutSequence;
    uint64_t &udpInSequence = msg.shouldAck() ? m_udpACKInSequence : m_udpInSequence;

    // rah shit, fragment too big. put the rest in the pool in case of network rating issue
    if (msgLen > MAX_UDP_PACKET_LENGTH) {
        // std::cout << "Msg Hash (" << udpOutSequence << " | " << msg.getSize() << "): " << msg.getHash() << std::endl;
        if (!m_udpPoolSend.addMessage(m_udpMyFragSequence, msg))
            return false;

        auto fragments = m_udpPoolSend.getMissingFragments(m_udpMyFragSequence, 0);
        bool res = sendDatagrams(socket, m_udpMyFragSequence, fragments);

        // temp : normally we should get the missing sequences, but for now we don't need them
        m_udpPoolSend.deleteSequence(m_udpMyFragSequence);

        m_udpMyFragSequence++;
        udpOutSequence++;
        return res;
    }

    UDPG_NetChannelHeader header = {.sequence = udpOutSequence, .ackFragmentSequence = m_udpFromFragSequence};
    if (msg.shouldAck())
        header.ack = m_udpACKFullInSequence;
    msg.writeHeader(header);

    size_t sent = socket.send(msg, *m_toUDPAddress);
    if (sent < 0) // guess it's send, but not quite, TODO : check any weird case (place breakpoint)
        return true;

    if (!msg.isFragmented())
        udpOutSequence++;

    /* for client/server rates calculation */
    m_udplastsent = Time::Clock::milliseconds();
    m_udplastsentsize = sent;
    return true;
}

bool NetChannel::readDatagram(SocketUDP &socket, UDPMessage &msg, size_t &readOffset) {
    UDPG_NetChannelHeader header;
    msg.readHeader(header, readOffset);

    // if (!NETCHAN_GENCHECKSUM(m_challenge, header.sequence))
    //     return false; /* what is going on sir ???? */

    uint64_t &udpOutSequence = msg.shouldAck() ? m_udpACKOutSequence : m_udpOutSequence;
    uint64_t &udpInSequence = msg.shouldAck() ? m_udpACKInSequence : m_udpInSequence;

    if (header.sequence <= udpInSequence) {
        /*out of order packet, delete it */
        // std::cout << "OOB packet: " << header.sequence << std::endl;
        return false;
    }

    if (msg.shouldAck()) { /* only care about reliable packets */
        m_udpACKClientLastACK = header.ack;
        m_droppedPackets = header.sequence - udpInSequence + 1;
    }

    /****** At this point, the packet is valid *******/

    if (msg.getType() == CL_SV_FRAGMENT) {
        UDPG_FragmentHeaderFrom fragHeader;
        msg.readContinuousData<UDPG_FragmentHeaderFrom>(fragHeader, readOffset);

        auto missing = m_udpPoolSend.getMissingFragments(fragHeader.idSequence, fragHeader.receivedFragmentsMask);
        if (missing.empty()) {
            m_udpPoolSend.deleteSequence(fragHeader.idSequence);
            return true;
        }
        sendDatagrams(socket, fragHeader.idSequence, missing);
        return true;
    }

    if (msg.isFragmented()) {
        uint32_t fragSequence;
        /* if true, that's a new sequence */
        if (m_udpPoolRecv.recvMessage(msg, readOffset, fragSequence, m_udpFromFragSequence)) {
            m_udpFromFragSequence = CF_NET_MAX(m_udpFromFragSequence, fragSequence);
            m_udpFragmentsOgSequences[fragSequence] = std::make_pair<>(header.sequence, 0);
        }

        if (m_udpPoolRecv.receivedFullSequence(fragSequence)) {
            msg = UDPMessage(true, msg.getType()); /* recreate */

            auto [sequence, _] = m_udpFragmentsOgSequences[fragSequence];
            m_udpFragmentsOgSequences.erase(fragSequence);
            if (sequence < m_udpACKFullInSequence) {
                std::cout << "RECV DELETED: " << sequence << " Msgsize: " << msg.getSize() << std::endl;
                return false; /* on se fait chier pour ça les gars !! */
            }

            m_udpPoolRecv.reconstructMessage(fragSequence, msg);
            // std::cout << "Msg Hash (" << sequence << "| "<< msg.getSize() <<"): " << msg.getHash() << std::endl;
            msg.writeHeader(header);
            msg.setWasFragmented(true);

            readOffset = 0;
            bool res = readDatagram(socket, msg, readOffset);
            m_udpPoolRecv.deleteSequence(fragSequence);
            m_udpACKFullInSequence = CF_NET_MAX(sequence, m_udpACKFullInSequence);
            return res;
        }
        return false;
    } else if (msg.shouldAck() && !msg.wasFragmented()) {
        m_udpACKFullInSequence = header.sequence;
    }

    m_udplastrecv = Time::Clock::milliseconds();

    udpInSequence = header.sequence;
    return true;
}

bool NetChannel::sendStream(const TCPMessage &msg) {
    if (!m_enabled || m_toTCPAddress == nullptr)
        return false;

    size_t sent = m_tcpSocket.send(msg);
    if (sent < 0)
        return false;

    return true;
}

bool NetChannel::readStream(TCPMessage &msg) {
    /* todo : add header check etc */

    try {
        m_tcpSocket.receive(msg);
    } catch (const SocketDisconnected &e) {
        m_disconnect = true;
        return true;
    }
    return true;
}

bool NetChannel::isTimeout() const {
    return Time::Clock::milliseconds() - m_udplastrecv > CVar::net_kick_timeout.getIntValue();
}

} // namespace Network