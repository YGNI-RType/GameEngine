/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** main.cpp
*/

#include "GEngine/game/Engine.hpp"
#include "GEngine/net/net.hpp"

int main(void) {
    Network::NET::init();

    Network::NET::initServer();

    auto &server = Network::NET::getServer();

    for (size_t i = 0; i < 10; i++) {
        Network::NET::sleep(300);
        if (!server.isRunning())
            continue;

        Network::UDPMessage msg(true, 4);
        const char *data = "Coucou je suis le serveir !!";
        msg.writeData(static_cast<const void *>(data), std::strlen(data));

        server.sendToAllClients(msg);
    }

    Network::NET::stop();
    return 0;
}
