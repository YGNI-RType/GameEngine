/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** queue
*/

#pragma once

#include "GEngine/net/msg.hpp"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <unordered_map>

namespace Network {
template <size_t NB_PACKETS, size_t MAX_PACKET_SIZE>
class NetQueue {
private:
    struct Segment {
        uint32_t id;
        uint8_t flag;
        size_t readCount = 0; /* only in incomming package */
    };

public:
    NetQueue() = default;

    bool push(const UDPMessage &msg, size_t readcount) {
        std::unique_lock<std::mutex> lock(m_mutex);

        if (msg.getSize() > MAX_PACKET_SIZE)
            return false;

        auto it = m_msgs.find(msg.getType());
        if (it == m_msgs.end())
            m_msgs[msg.getType()] = std::queue<Segment>();

        auto q = m_msgs[msg.getType()];
        auto idSegment = getFreeSegment();
        if (idSegment == -1)
            return false;

        Segment segment = {idSegment, msg.getFlags(), readcount};
        deconstructMessage(msg, segment);
        q.push(segment);
        m_nbUsed++;

        return true;
    }


    /* This is called when we know it's full, removes the front, same segment */
    bool fullpush(UDPMessage &msg, size_t readcount) {
        auto it = m_msgs.find(msg.getType());
        if (it == m_msgs.end())
            return false;

        auto &[_, queueSegment] = *it;

        auto segment = queueSegment.front();
        segment.readCount = readcount;
        segment.flag = msg.getFlags();

        queueSegment.pop();
        constructMessage(segment.id);
        queueSegment.push(segment);

        return true;
    }

    /* UDPMessage(false, <type you chose here> )*/
    bool pop(UDPMessage &msg, size_t &readCount, uint8_t type) {
        std::unique_lock<std::mutex> lock(m_mutex);

        auto it = m_msgs.find(type);
        if (it == m_msgs.end())
            return false;

        auto &[_, queueSegment] = *it;

        auto segment = queueSegment.front();
        queueSegment.pop();
        constructMessage(msg, segment, readCount);
        m_isUsed[segment.id] = false;
        m_nbUsed--;

        return true;
    }

    bool pop(UDPMessage &msg, size_t &readCount) {
        std::unique_lock<std::mutex> lock(m_mutex);

        for (auto &[type, queueSegment] : m_msgs) {
            if (queueSegment.empty())
                continue;

            auto segment = queueSegment.front();
            queueSegment.pop();
            constructMessage(msg, segment, readCount);
            msg.setType(type);
            m_isUsed[segment.id] = false;
            m_nbUsed--;

            return true;
        }

        return false;
    }

    bool empty(void) const {
        return m_nbUsed == 0;
    }

    bool full(void) const {
        return m_nbUsed == NB_PACKETS;
    }

    size_t size(void) const {
        return m_nbUsed;
    }

private:
    void constructMessage(UDPMessage &msg, const Segment &segment, size_t &readCount) const {
        msg.setFlag(segment.flag);
        msg.writeData(m_data.data() + segment.id * MAX_PACKET_SIZE, MAX_PACKET_SIZE);
        readCount = segment.readCount;
    }

    void deconstructMessage(const UDPMessage &msg, Segment &segment) {
        segment.flag = msg.getFlags();
        msg.readData(m_data.data() + segment.id * MAX_PACKET_SIZE, MAX_PACKET_SIZE);
    }

    uint32_t getFreeSegment(void) {
        if (full())
            return -1;

        for (uint32_t i = 0; i < NB_PACKETS; i++) {
            if (m_isUsed[i])
                continue;
            m_isUsed[i] = true;
            return i;
        }
        return -1;
    }

private:
    // std::queue<T> m_data;
    std::array<byte_t, NB_PACKETS * MAX_PACKET_SIZE> m_data;
    std::array<bool, NB_PACKETS> m_isUsed;
    std::atomic_size_t m_nbUsed = 0;
    std::unordered_map<uint8_t, std::queue<Segment>> m_msgs;

    mutable std::mutex m_mutex;
    // std::condition_variable m_cvNotEmpty;
    // std::condition_variable m_cvNotFull;
};

} // namespace Network
