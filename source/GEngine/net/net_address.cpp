/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** net_address
*/

#include "GEngine/net/net_address.hpp"
#include "GEngine/net/net_common.hpp"

#include <cstring>
#include <stdexcept>

namespace Network {

bool Address::operator==(const Address &other) const {
    if (m_type == AT_LOOPBACK)
        return true;

    if (m_type != other.getType())
        return false;

    if (m_port != other.getPort())
        return false;

    return isEqual(getData(), other.getData(), m_mask);
}

bool Address::isEqual(const byte_t *addr1, const byte_t *addr2, uint32_t mask) const {
    uint32_t curbyte = mask >> 3;
    uint32_t cmpmask;

    if (curbyte && std::memcmp(addr1, addr2, curbyte))
        return false;

    mask &= 0x07;
    if (mask) {
        cmpmask = (1 << mask) - 1;
        cmpmask <<= 8 - mask;

        if ((addr1[curbyte] & cmpmask) == (addr2[curbyte] & cmpmask))
            return true;
    } else
        return true;

    return false;
}

/**********************************************/

AddressV4::AddressV4(AddressType type, uint16_t port, const ipv4_t &address)
    : Address(type, port)
    , m_address(address) {
}
AddressV4::AddressV4(AddressType type, uint16_t port)
    : Address(type, port) {
}

AddressV4::AddressV4(AddressType type, uint16_t port, in_addr_t ip)
    : Address(type, port) {
    m_address = *(ipv4_t *)&ip;
}
AddressV4::AddressV4(AddressType type, const std::string &ip, uint16_t port)
    : Address(type, port) {
    in_addr_t addr = inet_addr(ip.c_str());

    if (addr == INADDR_NONE)
        throw std::runtime_error("Invalid IP address"); // todo : custom exception

    auto convAddr = ntohl(addr);

    m_address = *(ipv4_t *)&convAddr;
}

void AddressV4::toSockAddr(sockaddr *addr) const {
    struct sockaddr_in *s = reinterpret_cast<struct sockaddr_in *>(addr);

    s->sin_family = AF_INET;
    s->sin_port = htons(m_port);

    switch (m_type) {
    case AT_IPV4:
        s->sin_addr.s_addr = htonl(*(int *)&m_address);
        break;
    case AT_BROADCAST:
        s->sin_addr.s_addr = htonl(INADDR_BROADCAST);
        break;
    case AT_LOOPBACK:
        s->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        break;
    case AT_UNSPEC:
        s->sin_addr.s_addr = htonl(INADDR_ANY);
        break;
    default:
        break;
    }
}

bool AddressV4::isLanAddr(void) const {
    // RFC1918:
    // 10.0.0.0        -   10.255.255.255  (10/8 prefix)
    // 172.16.0.0      -   172.31.255.255  (172.16/12 prefix)
    // 192.168.0.0     -   192.168.255.255 (192.168/16 prefix)
    if (m_address[0] == 10 || m_address[0] == 127)
        return true;
    if (m_address[0] == 172 && m_address[1] >= 16 && m_address[1] <= 31)
        return true;
    if (m_address[0] == 192 && m_address[1] == 168)
        return true;
    return false;
}

/**********************************************/

AddressV6::AddressV6(AddressType type, uint16_t port, const ipv6_t &address, uint64_t scopeId)
    : Address(type, port)
    , m_address(address)
    , m_scopeId(scopeId) {
}
AddressV6::AddressV6(AddressType type, uint16_t port)
    : Address(type, port) {
}

AddressV6::AddressV6(AddressType type, uint16_t port, in6_addr ip, uint32_t scopeId)
    : Address(type, port)
    , m_scopeId(scopeId) {
    m_address = *(ipv6_t *)&ip;
    m_scopeId = scopeId;
}
AddressV6::AddressV6(AddressType type, const std::string &ip, uint16_t port)
    : Address(type, port) {
    in6_addr addr;

    if (inet_pton(AF_INET6, ip.c_str(), &addr) != 1)
        throw std::runtime_error("Invalid IP address"); // todo : custom exception

    m_address = *(ipv6_t *)&addr;
}

void AddressV6::toSockAddr(sockaddr *addr) const {
    struct sockaddr_in6 *s = reinterpret_cast<struct sockaddr_in6 *>(addr);

    s->sin6_family = AF_INET6;
    s->sin6_port = m_port;

    switch (m_type) {
    case AT_IPV6:
        s->sin6_addr = *((struct in6_addr *)&m_address);
        s->sin6_scope_id = m_scopeId;
        break;
    case AT_MULTICAST:
    case AT_UNSPEC:
        s->sin6_addr = in6addr_any;
        break;
    case AT_LOOPBACK:
        s->sin6_addr = in6addr_loopback;
        break;
    default:
        break;
    }
}

bool AddressV6::isLanAddr(void) const {
    // RFC4193:
    // fc00::/7
    // fd00::/8
    if (m_address[0] == 0xFE && m_address[1] == 0x80)
        return true;
    if ((m_address[0] & 0xfe) == 0xfc)
        return true;
    return false;
}

/************************************************************/

AddressV4 UnknownAddress::getV4() const {
    auto addr = reinterpret_cast<const sockaddr_in *>(&m_addr);

    return AddressV4(m_type, ntohs(addr->sin_port), htonl(addr->sin_addr.s_addr));
}

AddressV6 UnknownAddress::getV6() const {
    auto addr = reinterpret_cast<const sockaddr_in6 *>(&m_addr);

    return AddressV6(m_type, ntohs(addr->sin6_port), addr->sin6_addr, addr->sin6_scope_id);
}

void UnknownAddress::updateType(void) {
    if (m_addr.ss_family == AF_INET)
        m_type = AT_IPV4;
    else if (m_addr.ss_family == AF_INET6)
        m_type = AT_IPV6;
}
} // namespace Network