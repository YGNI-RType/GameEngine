/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** net
*/

#include "GEngine/cvar/net.hpp"

namespace CVar {
ConVar net_ipv6("net_ipv6", "0", ConVar::flag::CMD, "Enable ipv6 (set in convar)");

ConVar sv_maxplayers("sv_maxplayers", "4", ConVar::flag::TRANSMIT | ConVar::flag::SETUP,
                     "Set the maxmium number of players a server can accept");

ConVar net_recv_dropsim("net_recv_dropsim", "0", ConVar::flag::SELF, "Simulate recv packet drop rate (%)");
ConVar net_send_dropsim("net_send_dropsim", "0", ConVar::flag::SELF, "Simulate send packet drop rate (%)");

ConVar net_kick_timeout(
    "net_active_timeout", "10000", ConVar::flag::SELF,
    "Set the timeout to disconnect a client (self or server client) based on the last received packet");
} // namespace CVar
