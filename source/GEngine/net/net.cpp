/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** net
*/

// udp : why  the chunks are 1400 bytes long?
// https://stackoverflow.com/questions/1098897/what-is-the-largest-safe-udp-packet-size-on-the-internet

// for tcp : reliable messages (chat, image upload/download, game changes (map
// update, changing connection state of client)) for udp : unreliable messages
// (snapshot deltas/(full because dummy is set to all 0, meaning delta = full),
// voip)

// open both UDP socket for ipv4 and ipv6 for the same class
// add multicast for ipv6 --> NOT PRIORITARY
// https://en.wikipedia.org/wiki/NACK-Oriented_Reliable_Multicast

#include "GEngine/net/net.hpp"
#include "GEngine/cvar/net.hpp"
#include "GEngine/net/msg.hpp"
#include "GEngine/net/net_socket_error.hpp"

#include "GEngine/cvar/net.hpp"


#include <algorithm>
#include <cstring>
#include <thread>

#ifdef _WIN32
// TODO : remove unused

#include <winsock2.h>
#include <ws2spi.h>
#include <ws2tcpip.h>

typedef int socklen_t;
typedef u_long ioctlarg_t;

#define socketError WSAGetLastError()
#undef interface

#else
#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#if !defined(__sun) && !defined(__sgi)
#include <ifaddrs.h>
#endif

#define socketError errno

#endif

namespace Network {

/* Global vars */

SocketUDP NET::mg_socketUdp;
SocketTCPMaster NET::mg_socketListenTcp;
SocketUDP NET::mg_socketUdpV6;
SocketTCPMaster NET::mg_socketListenTcpV6;

NetServer NET::mg_server(mg_socketUdp, mg_socketUdpV6);
CLNetClient NET::mg_client(CVar::net_ipv6.getIntValue() ? mg_socketUdpV6 : mg_socketUdp,
                           CVar::net_ipv6.getIntValue() ? AT_IPV6 : AT_IPV4);

std::vector<IP> NET::g_localIPs;

std::thread NET::mg_networkThread;

uint16_t NET::currentUnusedPort = DEFAULT_PORT;

std::atomic_bool NET::mg_aEnable = false;
std::mutex NET::mg_mutex;

/***************/

void NET::init(void) {
    if (mg_aEnable)
        return;

    mg_aEnable = true;
    mg_networkThread = std::thread([]() {
        ASocket::initLibs();

        mg_socketUdp = openSocketUdp(currentUnusedPort, false);
        currentUnusedPort++;
        if (CVar::net_ipv6.getIntValue()) { // check if ipv6 is supported
            mg_socketUdpV6 = openSocketUdp(currentUnusedPort, true);
            currentUnusedPort++;
        }

        while (mg_aEnable)
            sleep(1000);
    });
}

void NET::initServer(gengine::interface::network::system::Snapshot &snapshot) {
    if (!NET::mg_aEnable)
        return;

    currentUnusedPort = NET::mg_server.start(CVar::sv_maxplayers.getIntValue(), currentUnusedPort, snapshot);
}

void NET::initClient(void) {
    if (!NET::mg_aEnable)
        return;

    mg_client.init();
}

void NET::stop(void) {
    NET::mg_server.stop();

    g_localIPs.clear();
    mg_aEnable = false;

    /* end of thread */
    mg_networkThread.join();
}

void NET::getLocalAddress(void) {
#if defined(__linux__) || defined(__APPLE__) || defined(__BSD__)
    struct ifaddrs *ifap;

    if (getifaddrs(&ifap))
        return; // throw error

    for (ifaddrs *search = ifap; search; search = search->ifa_next)
        if (ifap->ifa_flags & IFF_UP)
            addLocalAddress(search->ifa_name, search->ifa_addr, search->ifa_netmask, search->ifa_flags & IFF_LOOPBACK);

    freeifaddrs(ifap);

#else
    char hostname[256];
    struct addrinfo hint = {0};
    struct addrinfo *res = NULL;

    size_t numIP = 0;

    if (gethostname(hostname, 256) == SOCKET_ERROR)
        return;

    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_DGRAM;

    if (!getaddrinfo(hostname, NULL, &hint, &res)) {
        struct sockaddr_in mask4 = {0};
        struct sockaddr_in6 mask6 = {0};

        mask4.sin_family = AF_INET;
        std::memset(&mask4.sin_addr.s_addr, 0xFF, sizeof(mask4.sin_addr.s_addr));
        mask6.sin6_family = AF_INET6;
        std::memset(&mask6.sin6_addr, 0xFF, sizeof(mask6.sin6_addr));

        // add all IPs from returned list.
        for (struct addrinfo *search = res; search; search = search->ai_next)
            if (search->ai_family == AF_INET)
                addLocalAddress((char *)"", search->ai_addr, (struct sockaddr *)&mask4, search->ai_flags & AI_PASSIVE);
            else if (CVar::net_ipv6.getIntValue() && search->ai_family == AF_INET6)
                addLocalAddress((char *)"", search->ai_addr, (struct sockaddr *)&mask6, search->ai_flags & AI_PASSIVE);
    }

    if (res)
        freeaddrinfo(res);
#endif
}

void NET::addLocalAddress(char *ifname, struct sockaddr *sockaddr, struct sockaddr *netmask, bool isLoopback) {
    // only add addresses that have all required info.
    if (!sockaddr || !netmask || !ifname)
        return;

    sa_family_t family = sockaddr->sa_family;
    size_t addrlen;

    switch (family) {
    case AF_INET:
        addrlen = sizeof(struct sockaddr_in);
        break;
    case AF_INET6:
        addrlen = sizeof(struct sockaddr_in6);
        break;
    default:
        return;
    }

    IP ip = {.family = sockaddr->sa_family};

    if (family == AF_INET) {
        addrlen = sizeof(struct sockaddr_in);
        ip.type = AT_IPV4;
    } else if (family == AF_INET6) {
        addrlen = sizeof(struct sockaddr_in6);
        ip.type = AT_IPV6;
    } else
        return;

    ip.ifname = ifname;

    std::memcpy(&ip.addr, sockaddr, addrlen);
    std::memcpy(&ip.netmask, netmask, addrlen);

    return g_localIPs.push_back(ip);
}

void NET::sortLocalAddresses(void) {
    std::sort(g_localIPs.begin(), g_localIPs.end(), [](const IP &a, const IP &b) {
        if (a.type == AT_LOOPBACK)
            return true;
        if (b.type == AT_LOOPBACK)
            return false;

        if (a.type == AT_IPV4 && b.type == AT_IPV6)
            return true;
        if (a.type == AT_IPV6 && b.type == AT_IPV4)
            return false;

        return false;
    });
}

bool NET::isLanAddress(const Address &addr) {

    if (addr.getType() == AT_LOOPBACK)
        return true;

    return addr.isLanAddr();
}

/**************************************************************/

/* returns true if has event, false otherwise */
bool NET::sleep(uint32_t ms) {
    struct timeval timeout = {.tv_sec = static_cast<long>(ms / 1000u), .tv_usec = static_cast<int>((ms % 1000) * 1000)};
    SOCKET highest = ASocket::getHighestSocket();

    fd_set readSet;
    createSets(readSet);

    /* The usage of select : both on windows and unix systems */
    int res = select(highest + 1, &readSet, nullptr, nullptr, &timeout);
    if (res == -1)
        throw SocketException(strerror(socketError));
    else if (res == 0)
        return false;

    handleEvents(readSet);
    return true;
}

void NET::createSets(fd_set &readSet) {
    FD_ZERO(&readSet);

    mg_server.createSets(readSet);
    mg_client.createSets(readSet);

    mg_socketUdp.setFdSet(readSet);
    if (CVar::net_ipv6.getIntValue())
        mg_socketUdpV6.setFdSet(readSet);
}

bool NET::handleUdpEvent(SocketUDP &socket, UDPMessage &msg, const Address &addr) {
    if (mg_server.handleUDPEvent(socket, msg, addr))
        return true;

    return mg_client.handleUDPEvents(msg, addr);
}

bool NET::handleEvents(fd_set &readSet) {
    if (mg_socketUdp.isFdSet(readSet)) {
        UDPMessage msg(0, 0);
        while (true) {
            AddressV4 addr(AT_IPV6, 0);
            bool shouldContinue = mg_socketUdp.receiveV4(msg, addr);
            if (!shouldContinue)
                break;
            handleUdpEvent(mg_socketUdp, msg, addr);
        }
    }
    if (CVar::net_ipv6.getIntValue() && mg_socketUdpV6.isFdSet(readSet)) {
        UDPMessage msg(0, 0);
        while (true) {
            AddressV6 addr(AT_IPV6, 0);
            bool shouldContinue = mg_socketUdp.receiveV6(msg, addr);
            if (!shouldContinue)
                break;
            handleUdpEvent(mg_socketUdp, msg, addr);
        }
    }

    if (mg_server.handleTCPEvent(readSet))
        return true;

    return mg_client.handleTCPEvents(readSet);
}

/**************************************************************/

/* should it be bool ? should it returns a message instead of sending it directly ? */
void NET::pingServers(void) {
    if (CVar::net_ipv6.getIntValue())
        return mg_client.pingLanServers();
    return mg_client.pingLanServers();
}

} // namespace Network
