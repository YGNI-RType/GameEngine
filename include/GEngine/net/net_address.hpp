/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** net_address
*/

#pragma once

#include "net_common.hpp"

#include <array>

#ifdef _WIN32

typedef uint32_t in_addr_t;

#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace Network {
class Address {

protected:
    typedef std::array<byte_t, 4> ipv4_t;
    typedef std::array<byte_t, 16> ipv6_t;

public:
    virtual ~Address() = default;
    virtual void toSockAddr(sockaddr *addr) const = 0;
    virtual bool isLanAddr(void) const = 0;

    AddressType getType() const {
        return m_type;
    }
    uint16_t getPort() const {
        return m_port;
    }
    uint32_t getMask() const {
        return m_mask;
    }

    bool operator==(const Address &other) const;

    void setMask(uint32_t mask) {
        m_mask = mask;
    };

protected:
    virtual const byte_t *getData() const = 0;
    Address(AddressType type, uint16_t port)
        : m_type(type)
        , m_port(port) {
    }

    bool isEqual(const byte_t *addr1, const byte_t *addr2, uint32_t mask) const;

    AddressType m_type;
    uint16_t m_port;
    uint32_t m_mask = 0;
};

class AddressV4 : public Address {

public:
    AddressV4(AddressType type, uint16_t port, const ipv4_t &address);
    AddressV4(AddressType type, uint16_t port);
    AddressV4(AddressType type, uint16_t port, in_addr_t ip);
    AddressV4(AddressType type, const std::string &ip, uint16_t port);
    ~AddressV4() = default;

    const ipv4_t &getAddress() const {
        return m_address;
    }

    void toSockAddr(sockaddr *addr) const override final;
    bool isLanAddr(void) const override final;

private:
    const byte_t *getData() const override final {
        return m_address.data();
    }

    ipv4_t m_address;
};

class AddressV6 : public Address {

public:
    AddressV6(AddressType type, uint16_t port, const ipv6_t &address, uint64_t scopeId);
    AddressV6(AddressType type, uint16_t port);
    AddressV6(AddressType type, uint16_t port, in6_addr ip, uint32_t scopeId);
    AddressV6(AddressType type, const std::string &ip, uint16_t port);
    ~AddressV6() = default;

    const ipv6_t &getAddress() const {
        return m_address;
    }

    uint64_t getScopeId() const {
        return m_scopeId;
    };

    void toSockAddr(sockaddr *addr) const override final;
    bool isLanAddr(void) const override final;

private:
    const byte_t *getData() const override final {
        return m_address.data();
    }

    ipv6_t m_address;
    uint64_t m_scopeId;
};

class UnknownAddress {

public:
    UnknownAddress() = default;
    ~UnknownAddress() = default;

    AddressType getType(void) const {
        return m_type;
    }
    void updateType(void);
    AddressV6 getV6() const;
    AddressV4 getV4() const;

    sockaddr *getAddr(void) {
        return reinterpret_cast<sockaddr *>(&m_addr);
    }
    socklen_t &getLen(void) {
        return m_len;
    }

private:
    AddressType m_type = AT_NONE;
    sockaddr_storage m_addr = {0};
    socklen_t m_len = sizeof(m_addr);
};

} // namespace Network
