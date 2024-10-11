/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** ServerEvent.hpp
*/

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#include "GEngine/net/net.hpp"

namespace gengine::interface::network::system {
    class ServerEvent: public System<ServerEvent> {
    public:
        void init(void) override {
            subscribeToEvent<gengine::system::event::StartEngine>(&ServerEvent::onStartEngine);
            subscribeToEvent<gengine::system::event::MainLoop>(&ServerEvent::onMainLoop);
        }

        void onStartEngine(gengine::system::event::StartEngine &e) {
            auto &eventManager = Network::NET::getEventManager();

            eventManager.registerCallback<std::shared_ptr<Network::NetClient>>(
                Network::Event::CT_OnClientConnect, [this] (std::shared_ptr<Network::NetClient> client) {
                    std::cout << "new client !" << std::endl;
                }
            );
        }

        void onMainLoop(gengine::system::event::MainLoop &e) {

        }
    };
}