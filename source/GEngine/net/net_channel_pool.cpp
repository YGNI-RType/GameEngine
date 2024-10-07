/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_channel_pool
*/

#include "GEngine/net/net_channel.hpp"

namespace Network {
bool PacketPoolUdp::addMessage(uint32_t sequence, const UDPMessage &msg) {
    auto size = msg.getSize() / MAX_UDP_PACKET_LENGTH;
    auto remsize = msg.getSize() % MAX_UDP_PACKET_LENGTH;
    if (size > FRAG_SEQUENCE_TABLE_SZ)
        return false;

    m_poolSequences[sequence] =
        std::make_tuple<>(msg.getType(), static_cast<uint8_t>(size), static_cast<uint16_t>(remsize), m_pool.size());

    auto data = msg.getData();
    if (msg.hasHeader())
        data += sizeof(UDPG_NetChannelHeader);

    for (uint8_t i = 0; i < size; i++) {
        chunk_t chunk;
        std::memcpy(chunk.data(), data + i * CHUNK_SIZE, CHUNK_SIZE);
        m_pool.push_back(chunk);
    }

    chunk_t chunk;
    std::memcpy(chunk.data(), data + size * CHUNK_SIZE, remsize);
    m_pool.push_back(chunk);
    return true;
}

std::vector<const PacketPoolUdp::chunk_t *> PacketPoolUdp::getMissingFragments(uint32_t sequence, uint16_t mask) {
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end())
        return {};

    auto [type, size, remsize, offset] = it->second;
    std::vector<const chunk_t *> fragments;

    for (uint8_t i = 0; i < size; i++)
        if (!(mask & (1 << i)))
            fragments.push_back(&m_pool[offset + i]);
    if (!(mask & (1 << size)))
        fragments.push_back(&m_pool[offset + size]);
    return fragments;
}

void PacketPoolUdp::constructMessage(UDPMessage &msg, const chunk_t *chunk, size_t chunk_size,
                                     const UDPG_FragmentHeaderTo &header) {
    msg.appendData<UDPG_FragmentHeaderTo>(header);
    msg.appendData(chunk->data(), chunk_size);
}

bool PacketPoolUdp::deleteSequence(uint32_t sequence) {
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end())
        return false;

    auto [type, size, _, offset] = it->second;

    const auto maxSize = size * CHUNK_SIZE + 1;

    m_poolSequences.erase(sequence);
    m_pool.erase(m_pool.begin() + offset, m_pool.begin() + offset + size * CHUNK_SIZE + 1);

    /* update all the existing offsets of m_pool since we updated the indexes */
    for (auto &[_11, seq] : m_poolSequences) {
        auto &[_1, _2, _3, curOffset] = seq;
        if (curOffset > offset)
            curOffset -= maxSize;
    }

    return true;
}

/*****************************************************************/

/* tells if it's first time or not */
bool PacketPoolUdp::recvMessage(uint32_t sequence, const UDPMessage &msg, size_t &readOffset) {
    UDPG_FragmentHeaderTo header;
    msg.readContinuousData<UDPG_FragmentHeaderTo>(header, readOffset);
    size_t chunkSize = msg.getSize() - sizeof(UDPG_FragmentHeaderTo) - sizeof(UDPG_NetChannelHeader);
    size_t offset;
    bool isNewSequence = false;

    /* todo : add checks (mask <= 16, sizes 0 or extreme )*/
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end()) {
        auto t = std::make_tuple<>(msg.getType(), header.fragIdMax, 1 << header.fragId, m_pool.size());
        auto [type, size, cur_mask, offset] = t;
        m_poolSequences[sequence] = t;
        isNewSequence = true;
    } else {
        auto &[type, size, cur_mask, offset] = it->second;
        if (header.fragId > size)
            return isNewSequence; // impossible, break point here
        cur_mask |= 1 << header.fragId;
    }

    m_pool[offset + header.fragId] = chunk_t();
    std::memcpy(m_pool[offset + header.fragId].data(), msg.getData() + readOffset, chunkSize);
    return isNewSequence;
}

uint16_t PacketPoolUdp::getMask(uint32_t sequence) {
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end())
        return 0;
    return std::get<2>(it->second);
}

void PacketPoolUdp::reconstructMessage(uint32_t sequence, UDPMessage &msg) {
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end())
        return;

    auto [type, size, remsize, offset] = it->second;
    size_t totalSize = size * CHUNK_SIZE + remsize;
    msg = UDPMessage(false, type);

    for (uint8_t i = 0; i < size; i++)
        msg.appendData(m_pool[offset + i].data(), CHUNK_SIZE);
    msg.appendData(m_pool[offset + size].data(), remsize);
}

} // namespace Network
