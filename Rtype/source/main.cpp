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
#include "GEngine/interface/events/RemoteEvent.hpp"
#include "GEngine/interface/network/Networked.hpp"
#include "GEngine/interface/network/systems/ClientEventPublisher.hpp"
#include "GEngine/interface/network/systems/ServerEventReceiver.hpp"

//? ## GEngine Components ##
#include "GEngine/libdev/components/HitBoxs.hpp"
#include "GEngine/libdev/components/SpanLife.hpp"
#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/components/driver/output/Text.hpp"

//? ## GEngine Systems ##
#include "GEngine/libdev/systems/AutoKiller.hpp"
#include "GEngine/libdev/systems/Collisions.hpp"
#include "GEngine/libdev/systems/MainLoop.hpp"
#include "GEngine/libdev/systems/Motions.hpp"
#include "GEngine/libdev/systems/driver/input/KeyboardCatcher.hpp"
#include "GEngine/libdev/systems/driver/output/Animate.hpp"
#include "GEngine/libdev/systems/driver/output/Draw.hpp"
#include "GEngine/libdev/systems/driver/output/FontManager.hpp"
#include "GEngine/libdev/systems/driver/output/RenderWindow.hpp"
#include "GEngine/libdev/systems/driver/output/SoundManager.hpp"
#include "GEngine/libdev/systems/driver/output/TextureManager.hpp"

//? ### R-Type Components ###
#include "components/Background.hpp"
#include "components/Bullet.hpp"
#include "components/Caterpillar.hpp"
#include "components/Life.hpp"
#include "components/Monster.hpp"
#include "components/Plane.hpp"
#include "components/Player.hpp"
#include "components/Score.hpp"
#include "components/ScoreText.hpp"

//? ### R-Type Systems ###
#include "systems/BackgroundMotion.hpp"
#include "systems/CaterpillarsBound.hpp"
#include "systems/CaterpillarsWave.hpp"
#include "systems/ClearEntities.hpp"
#include "systems/DestroyOnCollision.hpp"
#include "systems/InputsToGameEvents.hpp"
#include "systems/PlanesAutoMotion.hpp"
#include "systems/PlanesWave.hpp"
#include "systems/PlayerAnimation.hpp"
#include "systems/PlayerMotion.hpp"
#include "systems/PlayerShoot.hpp"
#include "systems/Start.hpp"
#include "systems/UpdateScoreText.hpp"

//? ### R-Type Events ###
#include "events/Movement.hpp"
#include "events/Shoot.hpp"

namespace rtype {
void registerComponents(gengine::game::Engine &gameEngine, gengine::driver::Engine &driverEngine) {
    gameEngine.registerComponent<gengine::component::Transform2D>();
    gameEngine.registerComponent<gengine::component::Velocity2D>();
    gameEngine.registerComponent<gengine::component::driver::output::Animation>();
    gameEngine.registerComponent<gengine::component::driver::output::Drawable>();
    gameEngine.registerComponent<gengine::component::driver::output::Sprite>();
    gameEngine.registerComponent<gengine::component::driver::output::Text>();
    gameEngine.registerComponent<gengine::component::driver::output::Rectangle>();
    gameEngine.registerComponent<gengine::component::HitBoxSquare2D>();
    gameEngine.registerComponent<gengine::component::HitBoxCircle2D>();
    gameEngine.registerComponent<gengine::component::SpanLife>();

    gameEngine.registerComponent<component::Player>();
    gameEngine.registerComponent<component::Monster>();
    gameEngine.registerComponent<component::Background>();
    gameEngine.registerComponent<component::Bullet>();
    gameEngine.registerComponent<component::Plane>();
    gameEngine.registerComponent<component::Caterpillar>();
    gameEngine.registerComponent<component::Score>();
    gameEngine.registerComponent<component::ScoreText>();
    gameEngine.registerComponent<component::Life>();

    driverEngine.registerComponent<gengine::component::Transform2D>();
    driverEngine.registerComponent<gengine::component::Velocity2D>();
    driverEngine.registerComponent<gengine::component::driver::output::Animation>();
    driverEngine.registerComponent<gengine::component::driver::output::Drawable>();
    driverEngine.registerComponent<gengine::component::driver::output::Sprite>();
    driverEngine.registerComponent<gengine::component::driver::output::Text>();
    driverEngine.registerComponent<gengine::component::driver::output::Rectangle>();
    driverEngine.registerComponent<gengine::component::HitBoxSquare2D>();
    driverEngine.registerComponent<gengine::component::HitBoxCircle2D>();
    driverEngine.registerComponent<gengine::component::SpanLife>();

    driverEngine.registerComponent<component::Player>();
    driverEngine.registerComponent<component::Monster>();
    driverEngine.registerComponent<component::Background>();
    driverEngine.registerComponent<component::Bullet>();
    driverEngine.registerComponent<component::Plane>();
    driverEngine.registerComponent<component::Caterpillar>();
    driverEngine.registerComponent<component::Score>();
    driverEngine.registerComponent<component::ScoreText>();
    driverEngine.registerComponent<component::Life>();
}

void registerSystems(gengine::game::Engine &gameEngine, gengine::driver::Engine &driverEngine) {
    driverEngine.registerSystem<gengine::system::driver::output::RenderWindow>(1280, 750, "R-Type");
    driverEngine.registerSystem<gengine::system::driver::output::Draw2D>(BLACK);
    driverEngine.registerSystem<gengine::system::driver::output::DrawSprite>();
    driverEngine.registerSystem<gengine::system::driver::output::DrawText>();

    driverEngine.registerSystem<gengine::system::driver::output::TextureManager>("../assets/sprites");
    driverEngine.registerSystem<gengine::system::driver::output::FontManager>("../assets/fonts");
    driverEngine.registerSystem<gengine::system::driver::input::KeyboardCatcher>();
    driverEngine.registerSystem<system::InputsToGameEvents>();
    driverEngine.registerSystem<gengine::system::driver::output::SoundManager>("../assets/sounds");
    driverEngine.registerSystem<system::PlayerShoot>();

    gameEngine.registerSystem<gengine::system::driver::output::AnimationManager>("../assets/animations");
    gameEngine.registerSystem<gengine::system::driver::output::Animate>();
    gameEngine.registerSystem<gengine::system::Motion2D>();
    gameEngine.registerSystem<gengine::system::Collision2D>();
    gameEngine.registerSystem<gengine::system::AutoKiller>();
    gameEngine.registerSystem<system::Start>();
    gameEngine.registerSystem<system::CaterpillarsBound>();
    gameEngine.registerSystem<system::CaterpillarsWave>();
    gameEngine.registerSystem<system::PlanesAutoMotion>();
    gameEngine.registerSystem<system::PlanesWave>();
    gameEngine.registerSystem<system::PlayerMotion>();
    gameEngine.registerSystem<system::PlayerAnimation>();
    gameEngine.registerSystem<system::PlayerShoot>();
    gameEngine.registerSystem<system::BackgroundMotion>();
    gameEngine.registerSystem<system::ClearEntities>();
    gameEngine.registerSystem<system::DestroyOnCollision>();
    gameEngine.registerSystem<system::UpdateScoreText>();
}
} // namespace rtype

int main(int argc, char **argv) {
    std::string ip;
    if (argc > 1)
        ip = std::string(argv[1]);
    else
        ip = "127.0.0.1";
    gengine::driver::Engine driverEngine;
    gengine::game::Engine gameEngine;

    driverEngine.registerSystem<
        gengine::interface::network::system::ClientEventPublisher<rtype::event::Movement, rtype::event::Shoot>>();

    gameEngine.registerSystem<
        gengine::interface::network::system::ServerEventReceiver<rtype::event::Movement, rtype::event::Shoot>>();

    rtype::registerComponents(gameEngine, driverEngine);
    rtype::registerSystems(gameEngine, driverEngine);

    gengine::interface::network::Networked interface(driverEngine, gameEngine, ip, 4243, true);

    interface.run();
}
