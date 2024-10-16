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

#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/components/driver/output/Text.hpp"

#include "components/Background.hpp"
#include "components/Life.hpp"
#include "components/Monster.hpp"
#include "components/Player.hpp"
#include "components/Score.hpp"
#include "components/ScoreText.hpp"

// #include <format>
#include <random>

namespace rtype {
void system::Start::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&Start::onStartEngine);
    subscribeToEvent<gengine::interface::event::NewRemoteDriver>(&Start::onNewRemoteDriver);
    subscribeToEvent<gengine::interface::event::DeleteRemoteDriver>(&Start::onDeleteRemoteDriver);
}

void system::Start::onStartEngine(gengine::system::event::StartEngine &e) {
    spawnEntity(component::ScoreText(), gengine::component::Transform2D({1280 - 315, 726}, {2, 2}),
                gengine::component::driver::output::Drawable(2),
                gengine::component::driver::output::Text("arcade.ttf", "Score: 0", WHITE));
    // gengine::component::driver::output::Text("arcade.ttf", std::format("Score: {:08}", 0), WHITE));

    spawnEntity(component::Background(), gengine::component::Transform2D({0, 0}, {3.48, 3.48}),
                gengine::component::Velocity2D(-DEFAULT_BACKGROUND_SPEED, 0),
                gengine::component::driver::output::Drawable(0),
                gengine::component::driver::output::Sprite("r-typesheet0.png", Rectangle{0, 0, 1120, 207}, WHITE));

    spawnEntity(component::Background(), gengine::component::Transform2D({1119 * 3.48, 0}, {3.48, 3.48}),
                gengine::component::Velocity2D(-DEFAULT_BACKGROUND_SPEED, 0),
                gengine::component::driver::output::Drawable(0),
                gengine::component::driver::output::Sprite("r-typesheet0.png", Rectangle{0, 0, 1120, 207}, WHITE));

    for (std::size_t i = 0; i < 2; i++) {
        spawnEntity(component::Life(), gengine::component::Transform2D({99 - i * 66.f, 726}, {1, 1}, 0),
                    gengine::component::driver::output::Drawable(1),
                    gengine::component::driver::output::Sprite("r-typesheet42.gif", Rectangle{66, 0, 33, 17}, WHITE));
    }
}

void system::Start::onNewRemoteDriver(gengine::interface::event::NewRemoteDriver &e) {
    spawnEntity(
        component::Player(), gengine::component::Transform2D({0, float(rand() % 500)}, {3, 3}, 0),
        gengine::component::Velocity2D(0, 0), gengine::component::driver::output::Drawable(1),
        gengine::component::driver::output::Sprite("r-typesheet42.gif", Rectangle{66, 17.f * (m_nbPlayer % 5), 33, 17},
                                                   WHITE),
        gengine::component::HitBoxSquare2D(33, 17), gengine::interface::component::RemoteDriver(e.remote),
        gengine::component::driver::output::Animation("r-typesheet42.json/spaceship", 0.1f,
                                                      gengine::component::driver::output::AnimationTrack::Idling, 2),
        component::Score(0));
    m_nbPlayer++;
}

void system::Start::onDeleteRemoteDriver(gengine::interface::event::DeleteRemoteDriver &e) {
    auto &remotes = getComponents<gengine::interface::component::RemoteDriver>();
    for (auto &[entity, remote] : remotes) {
        if (remote == e.remote) {
            killEntity(entity);
            m_nbPlayer--;
            return;
        }
    }
}
} // namespace rtype
