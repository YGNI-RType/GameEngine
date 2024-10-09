/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_client
*/

#include "GEngine/net/net_client.hpp"

#include <algorithm>

// temp
#include <iostream>

namespace Network {
NetClient::NetClient(std::unique_ptr<Address> addr, SocketTCP &&socket, SocketUDP &socketudp)
    : m_channel(true, std::move(addr), std::move(socket))
    , m_socketUdp(socketudp) {
}

void NetClient::sendStream(const TCPMessage &msg) {
    if (!m_channel.isEnabled())
        return;

    m_channel.sendStream(msg);
}

bool NetClient::sendDatagram(UDPMessage &msg) {
    if (!m_channel.isEnabled())
        return false;

    return m_channel.sendDatagram(m_socketUdp, msg);
}

void NetClient::recvDatagram(UDPMessage &msg) {
    size_t readOffset = 0;

    m_channel.readDatagram(msg, readOffset);

    std::cout << "SV: client just sent UDP specific message" << std::endl;
}

bool NetClient::handleClientMsg(void) {
    TCPMessage msg(0);

    if (!m_channel.readStream(msg))
        return false;

    std::cout << "SV: client just sent TCP specific message" << std::endl;
    switch (msg.getType()) {
    case CL_CONNECT_INFORMATION: {
        TCPCL_ConnectInformation recvData;
        msg.readData<TCPCL_ConnectInformation>(recvData);

        m_channel.createUdpAddress(recvData.udpPort);
        return true;
    }
    default:
        return false;
    }
    return true;
}

bool NetClient::handleTCPEvents(fd_set &readSet) {
    auto &socket = m_channel.getTcpSocket();
    if (!socket.isFdSet(readSet))
        return false;

    socket.removeFdSet(readSet);
    return handleClientMsg();
}

/** Net Queue **/

bool NetClient::pushData(const UDPMessage &msg, bool shouldAck) {
    if (shouldAck)
        return m_packOutDataAck.push(msg);
    return m_packOutData.push(msg);
}

bool NetClient::popIncommingData(UDPMessage &msg) {
    return m_packInData.pop(msg, msg.getType());
}

bool NetClient::retrieveWantedOutgoingData(UDPMessage &msg) {
    return m_packOutData.pop(msg);
}

bool NetClient::retrieveWantedOutgoingDataAck(UDPMessage &msg) {
    return m_packOutDataAck.pop(msg);
}

bool NetClient::pushIncommingData(const UDPMessage &msg) {
    return m_packInData.push(msg);
}

/***************/

bool NetClient::sendPackets(void) {
    if (isDisconnected() || !m_channel.isEnabled())
        return false;

    size_t byteSent = 0;
    std::vector<bool (Network::NetClient::*)(Network::UDPMessage &)> vecFuncs = {
        &NetClient::retrieveWantedOutgoingData, &NetClient::retrieveWantedOutgoingDataAck};

    while (!vecFuncs.empty() || byteSent < m_maxRate) {
        UDPMessage msg(0, 0);
        auto retrieveFunc = vecFuncs.front();
        if ((this->*retrieveFunc)(msg)) {
            vecFuncs.erase(vecFuncs.begin());
            continue;
        }

        size_t size = msg.getSize();
        if (!sendDatagram(msg))
            return false; /* how */
        std::rotate(vecFuncs.begin(), vecFuncs.begin() + 1, vecFuncs.end());
        byteSent += size;
    }
    return true;
}

} // namespace Network
