/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** main.cpp
*/

// #include "GEngine/driver/Engine.hpp"
// #include "GEngine/game/Engine.hpp"
// #include "GEngine/interface/Internal.hpp"
// #include "GEngine/libdev/systems/MainLoop.hpp"
// #include "GEngine/libdev/systems/driver/input/KeyboardCatcher.hpp"
// #include "GEngine/libdev/systems/driver/output/Draw.hpp"
// #include "GEngine/libdev/systems/driver/output/RenderWindow.hpp"

// class Start : public gengine::System<Start> {
// public:
//     void init(void) override {
//         subscribeToEvent<gengine::system::event::StartEngine>(&Start::onStartEngine);
//     }

//     void onStartEngine(gengine::system::event::StartEngine &e) {
//         // spawnEntity(gengine::component::driver::output::Window(1080, 720, "window"),
//         //             gengine::component::driver::output::Color(RED));
//         spawnEntity(gengine::component::driver::output::Rectangle(0, 0, 50, 50),
//                     gengine::component::driver::output::Color(RED));
//         spawnEntity(gengine::component::driver::output::Rectangle(500, 500, 50, 50),
//                     gengine::component::driver::output::Color(BLACK));
//     }
// };

// class Logger : public gengine::System<Logger> {
// public:
//     void init(void) override {
//         subscribeToEvent<gengine::system::driver::input::KeyAEvent>(&Logger::onKeyA);
//     }


//     void onKeyA(gengine::system::driver::input::KeyAEvent &e) {
//         switch (e.state) {
//         case gengine::system::driver::input::InputState::RELEASE:
//             std::cout << "release" << std::endl;
//             break;
//         case gengine::system::driver::input::InputState::PRESSED:
//             std::cout << "pressed" << std::endl;
//             break;
//         case gengine::system::driver::input::InputState::DOWN:
//             std::cout << "down" << std::endl;
//             break;
//         default:
//             break;
//         }
//     }
// };

// #include "GEngine/libdev/systems/events/Native.hpp"

// #include "GEngine/libdev/System.hpp"

// #include "GEngine/libdev/components/HitBoxs.hpp"
// #include "GEngine/libdev/components/Motions.hpp"
// #include "GEngine/libdev/components/Positions.hpp"
// #include "GEngine/libdev/systems/Collisions.hpp"
// #include "GEngine/libdev/systems/Motions.hpp"

// class Start : public gengine::System<Start> {
// public:
//     void init(void) override { subscribeToEvent<gengine::system::event::StartEngine>(&Start::onStartEngine); }

//     void onStartEngine(gengine::system::event::StartEngine &e) {
//         spawnEntity(gengine::component::Position2D(0, 0), gengine::component::Motion2D(1, 0),
//                     gengine::component::HitBoxSquare2D(1, 1), gengine::component::Origin2D(0, 0));
//         spawnEntity(gengine::component::Position2D(10, 0), gengine::component::Motion2D(-1, 0),
//                     gengine::component::HitBoxSquare2D(1, 1));
//     }
// };

// #include "GEngine/libdev/systems/events/game/Collision.hpp"

// class HandleCollision : public gengine::System<HandleCollision> {
// public:
//     void init(void) override { subscribeToEvent<gengine::system::event::Collsion>(&HandleCollision::onCollision); }

//     void onCollision(gengine::system::event::Collsion &e) {
//         std::cout << "collision " << e.entity1 << "<->" << e.entity2 << std::endl;
//     }
// };

#include "GEngine/net/net.hpp"

#ifdef _WIN32
// TEMP TEMP TEMP : place it elsewhere, reminescence of windows.h from socket apis
#undef interface
#endif

int main(void) {
    Network::NET::init();

    Network::NET::initClient();
    // Network::NET::pingServers();

    Network::CLNetClient &client = Network::NET::getClient();

    client.connectToServer("127.0.0.1", 4243, true);

    for (size_t i = 0; i < 10; i++) {
        Network::NET::sleep(300);
        if (!client.isConnected()) {
            client.connectToServer(0);
            continue;
        }

        Network::UDPMessage msg(true, 3);
        const char *data = "Coucou je suis le client !!";
        msg.writeData((const void *)data, std::strlen(data));

        client.sendDatagram(msg);
    }

    Network::NET::stop();
    // gengine::game::Engine gameEngine;
    // gengine::driver::Engine driverEngine;

    // gameEngine.registerComponent<gengine::component::driver::output::Window>();
    // gameEngine.registerComponent<gengine::component::driver::output::Rectangle>();
    // gameEngine.registerComponent<gengine::component::driver::output::Color>();

    // gameEngine.registerSystem<Start>();
    // gameEngine.registerSystem<gengine::system::driver::input::KeyboardCatcher>();
    // gameEngine.registerSystem<Logger>();
    // gameEngine.registerSystem<gengine::system::AutoMainLoop>();
    // gameEngine.registerSystem<gengine::system::driver::output::RenderWindow>();
    // gameEngine.registerSystem<gengine::system::driver::output::Draw>();
    // gengine::interface::Internal interface(gameEngine, driverEngine);
    // interface.run();
}
