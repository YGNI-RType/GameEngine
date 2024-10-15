/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** main.cpp
*/

// TODO reorder include

//? ## Engine ##
#include "GEngine/driver/Engine.hpp"
#include "GEngine/game/Engine.hpp"
#include "GEngine/interface/Internal.hpp"
// #include "GEngine/interface/network/Networked.hpp"

//? ## GEngine Components ##
#include "GEngine/libdev/components/HitBoxs.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"

//? ## GEngine Systems ##
#include "GEngine/libdev/systems/Collisions.hpp"
#include "GEngine/libdev/systems/MainLoop.hpp"
#include "GEngine/libdev/systems/Motions.hpp"
#include "GEngine/libdev/systems/driver/input/KeyboardCatcher.hpp"
#include "GEngine/libdev/systems/driver/output/Animate.hpp"
#include "GEngine/libdev/systems/driver/output/Draw.hpp"
#include "GEngine/libdev/systems/driver/output/RenderWindow.hpp"
#include "GEngine/libdev/systems/driver/output/TextureManager.hpp"

//? ### R-Type Components ###

#include "components/Background.hpp"
#include "components/Bullet.hpp"
// #include "components/Fire.hpp"
#include "components/Monster.hpp"
#include "components/Player.hpp"
#include "components/PlayerControl.hpp"

//? ### R-Type Systems ###
#include "systems/BackgroundMotion.hpp"
#include "systems/ClearBullets.hpp"
#include "systems/DestroyOnCollision.hpp"
#include "systems/MonstersAutoMotion.hpp"
#include "systems/PlayerMotion.hpp"
#include "systems/PlayerShoot.hpp"
#include "systems/Start.hpp"

namespace rtype {
void registerComponents(gengine::game::Engine &gameEngine, gengine::driver::Engine &driverEngine) {
    gameEngine.registerComponent<gengine::component::Transform2D>();
    gameEngine.registerComponent<gengine::component::Velocity2D>();
    gameEngine.registerComponent<gengine::component::driver::output::Animation>();
    gameEngine.registerComponent<gengine::component::driver::output::Drawable>();
    gameEngine.registerComponent<gengine::component::driver::output::Sprite>();
    gameEngine.registerComponent<gengine::component::driver::output::Rectangle>();
    gameEngine.registerComponent<gengine::component::HitBoxSquare2D>();
    gameEngine.registerComponent<gengine::component::HitBoxCircle2D>();

    gameEngine.registerComponent<component::Player>();
    gameEngine.registerComponent<component::PlayerControl>();
    gameEngine.registerComponent<component::Monster>();
    gameEngine.registerComponent<component::Background>();
    gameEngine.registerComponent<component::Bullet>();

    driverEngine.registerComponent<gengine::component::Transform2D>();
    driverEngine.registerComponent<gengine::component::Velocity2D>();
    driverEngine.registerComponent<gengine::component::driver::output::Animation>();
    driverEngine.registerComponent<gengine::component::driver::output::Drawable>();
    driverEngine.registerComponent<gengine::component::driver::output::Sprite>();
    driverEngine.registerComponent<gengine::component::driver::output::Rectangle>();
    driverEngine.registerComponent<gengine::component::HitBoxSquare2D>();
    driverEngine.registerComponent<gengine::component::HitBoxCircle2D>();

    driverEngine.registerComponent<component::Player>();
    driverEngine.registerComponent<component::PlayerControl>();
    driverEngine.registerComponent<component::Monster>();
    driverEngine.registerComponent<component::Background>();
    driverEngine.registerComponent<component::Bullet>();
    // gameEngine.registerComponent<component::Fire>();
}

struct Test : public gengine::System<Test> {
    void init(void) override {
        subscribeToEvent<
            gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_Left>>(
            &Test::onKey_Left);
        subscribeToEvent<
            gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_Right>>(
            &Test::onKey_Right);
        subscribeToEvent<
            gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_Up>>(
            &Test::onKey_Up);
        subscribeToEvent<
            gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_Down>>(
            &Test::onKey_Down);
        subscribeToEvent<gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_P>>(
            &Test::onKey_P);
        subscribeToEvent<gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_O>>(
            &Test::onKey_O);
    }

    void
    onKey_Left(gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_Left> &e) {
        std::cout << "Left" << std::endl;
    }

    void
    onKey_Right(gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_Right> &e) {
        std::cout << "Right" << std::endl;
    }

    void onKey_Up(gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_Up> &e) {
        std::cout << "Up" << std::endl;
    }

    void
    onKey_Down(gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_Down> &e) {
        std::cout << "Down" << std::endl;
    }

    void onKey_P(gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_P> &e) {
        std::cout << "P" << std::endl;
    }

    void onKey_O(gengine::interface::network::event::RemoteEvent<gengine::system::event::driver::input::Key_O> &e) {
        std::cout << "O" << std::endl;
    }
};

void registerSystems(gengine::game::Engine &gameEngine, gengine::driver::Engine &driverEngine) {

    // gameEngine.registerSystem<gengine::system::driver::output::RenderWindow>(1280, 720, "R-Type");
    // gameEngine.registerSystem<gengine::system::driver::output::Draw2D>();
    // gameEngine.registerSystem<gengine::system::driver::output::DrawSprite>();
    // gameEngine.registerSystem<gengine::system::driver::output::Animate>();
    // gameEngine.registerSystem<gengine::system::driver::output::TextureManager>("../assets/sprites");
    // gameEngine.registerSystem<gengine::system::driver::input::KeyboardCatcher>();

    gameEngine.registerSystem<gengine::system::Motion2D>();
    gameEngine.registerSystem<gengine::system::Collision2D>();
    gameEngine.registerSystem<system::Start>();
    gameEngine.registerSystem<system::MonstersAutoMotion>();
    gameEngine.registerSystem<system::PlayerMotion>();
    gameEngine.registerSystem<system::PlayerShoot>();
    gameEngine.registerSystem<system::BackgroundMotion>();
    gameEngine.registerSystem<system::ClearBullets>();
    gameEngine.registerSystem<system::DestroyOnCollision>();
    gameEngine.registerSystem<gengine::system::driver::output::Animate>();

    driverEngine.registerSystem<gengine::system::driver::output::RenderWindow>(1280, 720, "R-Type");
    driverEngine.registerSystem<gengine::system::driver::output::Draw2D>();
    driverEngine.registerSystem<gengine::system::driver::output::DrawSprite>();
    driverEngine.registerSystem<gengine::system::driver::output::TextureManager>("../assets/sprites");
    driverEngine.registerSystem<gengine::system::driver::input::KeyboardCatcher>();

    // driverEngine.registerSystem<gengine::system::Motion2D>();
    // driverEngine.registerSystem<gengine::system::Collision2D>();
    // driverEngine.registerSystem<system::Start>();
    // driverEngine.registerSystem<system::MonstersAutoMotion>();
    // driverEngine.registerSystem<system::PlayerMotion>();
    // driverEngine.registerSystem<system::PlayerShoot>();
    // driverEngine.registerSystem<system::BackgroundMotion>();
    // driverEngine.registerSystem<system::ClearBullets>();
    // driverEngine.registerSystem<system::DestroyOnCollision>();
}
} // namespace rtype

#include "GEngine/interface/network/Networked.hpp"
#include "GEngine/interface/network/systems/ClientEventPublisher.hpp"
#include "GEngine/interface/network/systems/ServerEventReceiver.hpp"
#include "GEngine/interface/network/systems/Updater.hpp"
// #include "GEngine/interface/network/events/ClientEvent.hpp"

int main(int argc, char **argv) {
    std::string ip;
    if (argc > 1) {
        ip = std::string(argv[1]);
    } else
        ip = "127.0.0.1";

    gengine::game::Engine gameEngine;
    gengine::driver::Engine driverEngine;
    // gengine::interface::network::Networked interface(gameEngine, driverEngine);

    driverEngine.registerSystem<gengine::interface::network::system::ClientEventPublisher<
        gengine::system::event::driver::input::Key_Left, gengine::system::event::driver::input::Key_Right,
        gengine::system::event::driver::input::Key_Up, gengine::system::event::driver::input::Key_Down,
        gengine::system::event::driver::input::Key_P, gengine::system::event::driver::input::Key_O>>();

    gameEngine.registerSystem<gengine::interface::network::system::ServerEventReceiver<
        gengine::system::event::driver::input::Key_Left, gengine::system::event::driver::input::Key_Right,
        gengine::system::event::driver::input::Key_Up, gengine::system::event::driver::input::Key_Down,
        gengine::system::event::driver::input::Key_P, gengine::system::event::driver::input::Key_O>>();

    rtype::registerComponents(gameEngine, driverEngine);
    rtype::registerSystems(gameEngine, driverEngine);

    // gameEngine.registerSystem<rtype::Test>();
    // gengine::interface::network::Networked interface(driverEngine, gameEngine, "10.8.0.1", 4243, true);
    gengine::interface::network::Networked interface(driverEngine, gameEngine, ip, 4243, true);
    interface.run();
}
