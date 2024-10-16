/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_channel_pool
*/

#include "GEngine/net/net_channel.hpp"

#include <algorithm>

#include <iostream>

namespace Network {
bool PacketPoolUdp::addMessage(uint32_t sequence, const UDPMessage &msg) {
    size_t msgSize = msg.getSize() - (msg.hasHeader() ? sizeof(UDPG_NetChannelHeader) : 0);
    auto size = msgSize / CHUNK_SIZE;
    auto remsize = msgSize % CHUNK_SIZE;
    if (size > FRAG_SEQUENCE_TABLE_SZ)
        return false;

    m_poolSequences[sequence] = std::make_tuple<>(msg.getType(), msg.getFlags(), static_cast<uint8_t>(size),
                                                  static_cast<uint16_t>(remsize), 0, m_pool.size());

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

    auto [type, flag, size, remsize, _recvmask, offset] = it->second;
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
    msg.appendData((const void *)(chunk->data()), chunk_size);
}

bool PacketPoolUdp::deleteSequence(uint32_t sequence) {
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end())
        return false;

    auto [type, flag, size, last_recv, _recvmask, offset] = it->second;

    m_poolSequences.erase(sequence);
    m_pool.erase(m_pool.begin() + offset + 1, m_pool.begin() + offset + size + 1);

    /* update all the existing offsets of m_pool since we updated the indexes */
    for (auto &[_11, seq] : m_poolSequences) {
        auto &[_1, _2, _3, _4, _5, curOffset] = seq;
        if (curOffset > offset)
            curOffset -= size;
    }

    return true;
}

/*****************************************************************/

/* tells if it's first time or not */
bool PacketPoolUdp::recvMessage(const UDPMessage &msg, size_t &readOffset, uint32_t &fragSequence,
                                const uint32_t &maxFragSeq) {
    UDPG_FragmentHeaderTo header;
    msg.readContinuousData<UDPG_FragmentHeaderTo>(header, readOffset);

    fragSequence = header.idSequence;
    size_t chunkSize = msg.getSize() - sizeof(UDPG_FragmentHeaderTo) - sizeof(UDPG_NetChannelHeader);
    bool isLast = header.fragId == header.fragIdMax;
    size_t offset;
    bool isNewSequence = false;

    // std::cout << "(" << header.idSequence << ") RECV fragment: " << (int)header.fragId << " | " << msg.getSize() << "
    // H: " << msg.getHash() << std::endl;

    /* todo : add checks (mask <= 16, sizes 0 or extreme )*/
    auto it = m_poolSequences.find(fragSequence);
    if (it == m_poolSequences.end()) {
        if (header.idSequence < maxFragSeq)
            return false;

        /* todo : add something that cleans (thread that cleans or something) */
        auto t = std::make_tuple<>(msg.getType(), msg.getFlags(), header.fragIdMax, isLast ? chunkSize : 0,
                                   1 << header.fragId, m_pool.size());
        auto [type, flag, size, last_recv, cur_mask, _offset] = t;
        m_poolSequences[fragSequence] = t;
        isNewSequence = true;
        offset = _offset;
        m_pool.resize(offset + size + 1);
    } else {
        auto &[type, flag, size, last_size, cur_mask, _offset] = it->second;
        if (header.fragId > size)
            return isNewSequence; // impossible, break point here

        if (cur_mask & 1 << header.fragId)
            return isNewSequence; // already received
        cur_mask |= 1 << header.fragId;
        offset = _offset;
        if (isLast)
            last_size = chunkSize;
    }

    // m_pool.emplace(m_pool.begin() + offset + header.fragId, chunk_t());
    std::memcpy(m_pool[offset + header.fragId].data(), msg.getData() + readOffset, chunkSize);
    return isNewSequence;
}

std::pair<uint32_t, uint16_t> PacketPoolUdp::getCurrentSequence(void) {
    if (m_poolSequences.size() == 0)
        return std::make_pair<>(-1, 0);

    auto it = m_poolSequences.begin();
    return std::make_pair<>(it->first, std::get<4>(it->second));
}

uint16_t PacketPoolUdp::getMask(uint32_t sequence) {
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end())
        return 0;
    return std::get<4>(it->second);
}

void PacketPoolUdp::reconstructMessage(uint32_t sequence, UDPMessage &msg) {
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end())
        return;

    auto [type, flags, size, last_size, mask_size, offset] = it->second;
    size_t totalSize = sizeof(UDPG_NetChannelHeader) + size * CHUNK_SIZE + last_size;
    msg.setFlag(flags);
    msg.setFragmented(false);

    for (uint8_t i = 0; i < size; i++)
        msg.appendData((const void *)m_pool[offset + i].data(), CHUNK_SIZE);
    msg.appendData((const void *)m_pool[offset + size].data(), last_size);
}

bool PacketPoolUdp::receivedFullSequence(uint32_t sequence) {
    auto it = m_poolSequences.find(sequence);
    if (it == m_poolSequences.end())
        return false; // or handle the error as needed

    auto idmax = (std::get<2>(it->second));
    uint8_t wanted = (1 << idmax);
    for (int i = 0; i < idmax; i++)
        wanted |= (1 << i);
    auto curMask = getMask(sequence);
    return curMask == wanted;
}

} // namespace Network
