/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** msg
*/

#include "GEngine/net/msg.hpp"
#include "GEngine/net/net_socket.hpp"

namespace Network {
UDPMessage::UDPMessage(bool hasHeader, uint8_t type)
    : AMessage(type) {
    m_curSize = hasHeader ? sizeof(UDPG_NetChannelHeader) : 0;
}

UDPMessage &UDPMessage::operator=(const UDPMessage &other) {
    m_flags = other.m_flags;
    m_curSize = other.m_curSize;
    m_type = other.m_type;
    std::memcpy(m_data, other.m_data, m_curSize);
    return *this;
}

void UDPMessage::setSerialize(UDPSerializedMessage &msg) {
    m_type = msg.type;
    m_flags = msg.flag;
    std::memcpy(m_data, &msg.data, msg.curSize);
    m_curSize = msg.curSize;
}

void UDPMessage::getSerialize(UDPSerializedMessage &msg) const {
    msg.type = m_type;
    msg.curSize = m_curSize;
    msg.flag = m_flags;
    std::memcpy(&msg.data, m_data, m_curSize);
}

void UDPMessage::writeHeader(const UDPG_NetChannelHeader &header) {
    /* bypasses the m_cursize, since normally, it should contain this exact amount of data inside */
    std::memcpy(m_data, &header, sizeof(UDPG_NetChannelHeader));
}

void UDPMessage::readHeader(UDPG_NetChannelHeader &header, size_t &readOffset) const {
    std::memcpy(&header, m_data, sizeof(UDPG_NetChannelHeader));
    readOffset += sizeof(UDPG_NetChannelHeader);
}

void UDPMessage::setCompressed(bool compressed) {
    if (compressed)
        m_flags |= COMPRESSED;
    else
        m_flags &= ~COMPRESSED;
}

void UDPMessage::setHeader(bool header) {
    if (header)
        m_flags |= HEADER;
    else
        m_flags &= ~HEADER;
}

void UDPMessage::setFragmented(bool fragmented) {
    if (fragmented)
        m_flags |= FRAGMENTED;
    else
        m_flags &= ~FRAGMENTED;
}

void UDPMessage::setEncrypted(bool encrypted) {
    if (encrypted)
        m_flags |= ENCRYPTED;
    else
        m_flags &= ~ENCRYPTED;
}

void UDPMessage::setAck(bool ack) {
    if (ack)
        m_flags |= ACK;
    else
        m_flags &= ~ACK;
}

uint64_t UDPMessage::getAckNumber(void) const {
    if (!shouldAck())
        return 0;
    UDPG_NetChannelHeader header;

    readData<UDPG_NetChannelHeader>(header);
    return header.ack;
}

void UDPMessage::clear(void) {
    memset(m_data + sizeof(UDPG_NetChannelHeader), 0, m_curSize);
}
} // namespace Network
