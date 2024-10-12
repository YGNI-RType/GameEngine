/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** net_common
*/

#pragma once

#include <cstdint>
#include <string>

#ifdef _WIN32
#include <WS2tcpip.h>
#include <winsock2.h>

#undef interface

#else
#include <sys/socket.h>
#endif

namespace Network {

#ifndef IF_NAMESIZE
#define IF_NAMESIZE 16
#endif

#ifdef _WIN32
#ifdef ADDRESS_FAMILY
#define sa_family_t ADDRESS_FAMILY
#else
typedef unsigned short sa_family_t;
#undef interface
#endif
#define socketError WSAGetLastError()
#else /* unix */
#define WSAEINVAL EINVAL
#define WSAEALREADY EALREADY
#define WSAEWOULDBLOCK EWOULDBLOCK
#define WSATRY_AGAIN EAGAIN
#define WSAEMSGSIZE EMSGSIZE
#define WSAEINTR EINTR
#define WSAEINPROGRESS EINPROGRESS
#define WSAEADDRINUSE EADDRINUSE
#define WSAENOTSOCK EBADF
#define WSAECONNRESET ECONNRESET
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR -1
#define socketError errno
#endif

#define PORT_ANY -1
#define MAX_LISTEN 5
#define MAX_TRY_PORTS 5
#define DEFAULT_PORT 4242

#define MAX_CLIENTS 100

/* Due to MTU possible fragmentation, making the request even slower */
#define MAX_UDP_PACKET_LENGTH 1450 /* wi-fi : ~1472 / ethernet : 1500 */

#define MAX_UDP_MSGLEN 16384
#define MAX_TCP_MSGLEN 32768

#define CF_NET_MIN(a, b) ((a) < (b) ? (a) : (b))
#define CF_NET_MAX(a, b) ((a) > (b) ? (a) : (b))
#define CF_NET_CLAMP(x, a, b) CF_NET_MIN(CF_NET_MAX(x, a), b)

typedef uint8_t byte_t;

typedef enum { AT_NONE = 0, AT_BOT, AT_LOOPBACK, AT_BROADCAST, AT_MULTICAST, AT_IPV4, AT_IPV6, AT_UNSPEC } AddressType;

struct IP {
    std::string ifname = std::string(IF_NAMESIZE, '\0');

    AddressType type;
    sa_family_t family;
    struct sockaddr_storage addr;
    struct sockaddr_storage netmask;
};
} // namespace Network
