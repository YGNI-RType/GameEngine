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
    };

public:
    NetQueue() = default;

    bool push(const UDPMessage &msg) {
        std::unique_lock<std::mutex> lock(m_mutex);
        // m_cvNotFull.wait(lock, [this] { return m_nbUsed; });

        if (msg.getSize() > MAX_PACKET_SIZE)
            return false;

        auto it = m_msgs.find(msg.getType());
        if (it == m_msgs.end())
            m_msgs[msg.getType()] = std::queue<Segment>();

        auto q = m_msgs[msg.getType()];
        auto idSegment = getFreeSegment();
        if (idSegment == -1)
            return false;

        Segment segment = {idSegment, msg.getFlags()};
        deconstructMessage(msg, segment);
        q.push(segment);
        m_nbUsed++;

        // m_cvNotEmpty.notify_one();
        return true;
    }

    /* UDPMessage(false, <type you chose here> )*/
    bool pop(UDPMessage &msg, uint8_t type) {
        std::unique_lock<std::mutex> lock(m_mutex);
        // m_cvNotEmpty.wait(lock, [this] { return !m_data.empty(); });

        auto it = m_msgs.find(type);
        if (it == m_msgs.end())
            return false;

        auto &[_, queueSegment] = *it;

        auto segment = queueSegment.front();
        constructMessage(msg, segment);
        m_isUsed[segment.id] = false;
        m_nbUsed--;

        // m_cvNotFull.notify_one();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_data.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_data.size();
    }

private:
    void constructMessage(UDPMessage &msg, Segment &segment) const {
        msg.setFlag(segment.flag);
        msg.writeData(m_data.data() + segment.id * MAX_PACKET_SIZE, MAX_PACKET_SIZE);
    }

    void deconstructMessage(UDPMessage &msg, Segment &segment) const {
        segment.flag = msg.getFlags();
        msg.readData(m_data.data() + segment.id * MAX_PACKET_SIZE, MAX_PACKET_SIZE);
    }

    uint32_t getFreeSegment(void) {
        if (m_nbUsed == NB_PACKETS)
            return -1;

        for (uint32_t i = 0; i < NB_PACKETS; i++) {
            if (m_isUsed[i])
                continue;
            m_isUsed[i] = true;
            return i;
        }
    }

private:
    // std::queue<T> m_data;
    std::array<byte_t, NB_PACKETS * MAX_PACKET_SIZE> m_data;
    std::array<bool, NB_PACKETS> m_isUsed;
    size_t m_nbUsed = 0;
    std::unordered_map<uint8_t, std::queue<Segment>> m_msgs;

    mutable std::mutex m_mutex;
    // std::condition_variable m_cvNotEmpty;
    // std::condition_variable m_cvNotFull;
};

} // namespace Network
