/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Start.hpp
*/

#include "systems/Start.hpp"

#include "GEngine/libdev/components/HitBoxs.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/Velocities.hpp"

#include "GEngine/interface/components/RemoteDriver.hpp"
#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/components/driver/output/Text.hpp"

#include "components/Background.hpp"
#include "components/Monster.hpp"
#include "components/Player.hpp"
#include "components/PlayerControl.hpp"

#include <random>

namespace rtype::system {
void Start::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&Start::onStartEngine);
    subscribeToEvent<gengine::interface::event::NewRemoteDriver>(&Start::onNewRemoteDriver);
    subscribeToEvent<gengine::interface::event::DeleteRemoteDriver>(&Start::onDeleteRemoteDriver);
}

void Start::onStartEngine(gengine::system::event::StartEngine &e) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> transformXFork(0 + 80, 1280 - 160);
    std::uniform_int_distribution<> transformYFork(0 + 80, 720 - 160);

    // for (std::size_t i = 0; i < 1; i++) {
    float x = transformXFork(gen);
    float y = transformYFork(gen);

    spawnEntity(gengine::component::Transform2D({x, y}, {2, 2}, 0), gengine::component::Velocity2D(0, 0),
                gengine::component::driver::output::Sprite("r-typesheet3.gif", Rectangle{0, 0, 17, 18}, WHITE),
                gengine::component::driver::output::Animation(12, rand() % 12, 0.1f),
                gengine::component::driver::output::Drawable(1), component::Monster("poulet"),
                gengine::component::HitBoxSquare2D(17, 18));
    // }
    // gengine::component::driver::output::Animation(5, 0, 0.2f, true));

    spawnEntity(component::Background(), gengine::component::Transform2D({0, 0}, {3.48, 3.48}),
                gengine::component::Velocity2D(-2, 0), gengine::component::driver::output::Drawable(0),
                gengine::component::driver::output::Sprite("r-typesheet0.png", Rectangle{0, 0, 1226, 207}, WHITE));
}

void Start::onNewRemoteDriver(gengine::interface::event::NewRemoteDriver &e) {
    std::cout << "new player" << std::endl;
    spawnEntity(component::Player("Arcod"), component::PlayerControl(),
                gengine::component::Transform2D({0, static_cast<float>(rand() % 720)}, {3, 3}, 0),
                gengine::component::Velocity2D(0, 0), gengine::component::driver::output::Drawable(1),
                gengine::component::driver::output::Sprite("r-typesheet1.gif", Rectangle{167, 0, 33, 17}, WHITE),
                gengine::component::HitBoxSquare2D(33 * 2, 17 * 2),
                gengine::interface::component::RemoteDriver(e.remote));
}

void Start::onDeleteRemoteDriver(gengine::interface::event::DeleteRemoteDriver &e) {
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();

    for (auto &[entity, remote] : remotes) {
        if (remote == e.remote) {
            killEntity(entity);
            return;
        }
    }
}
} // namespace rtype::system
