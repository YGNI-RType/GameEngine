/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet (Workspace)
** File description:
** msg_tcp_structs
*/

#pragma once

#include "GEngine/net/utils/pack.hpp"

namespace Network {
enum {
    SV_INIT_CONNECTON,
    SV_YOU_ARE_READY,
    SV_DOWNLOAD,
    SV_UPLOAD, // TODO : add resriction on files (size, type, etc)
};

enum {
    CL_CONNECT_INFORMATION,
    CL_DOWNLOAD,
    CL_UPLOAD,
};

PACK(struct TCPSV_ClientInit {
    uint32_t challenge;
    uint16_t udpPort;
    // todo : add more information, that client needs to know that the server won't change
});

struct TCPCL_ConnectInformation {
    uint16_t udpPort;

    /* todo: add the name, client information */
};

} // namespace Network
