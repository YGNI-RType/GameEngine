/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** msg
*/

#include "GEngine/net/msg.hpp"

namespace Network {
AMessage::AMessage(uint8_t type)
    : m_type(type) {
}

void AMessage::writeData(const void *data, std::size_t size) {
    byte_t *myData = getDataMember();
    std::memcpy(myData + m_curSize, data, size);
    m_curSize += size;
}

void AMessage::readData(void *data, std::size_t size) const {
    if (size > m_curSize)
        throw std::runtime_error("Not enough data to read");

    const byte_t *myData = getData();
    std::memcpy(data, myData + m_curSize, size);
}

} // namespace Network
