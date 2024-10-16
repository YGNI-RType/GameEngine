/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** PlanesWave.cpp
*/

#include "systems/PlanesWave.hpp"

#include <random>

namespace rtype::system {
void PlanesWave::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&PlanesWave::onGameLoop);
}

void PlanesWave::onGameLoop(gengine::system::event::GameLoop &e) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> change_spawn_vawe(0, 50);

    if (change_spawn_vawe(gen) == 0)
        spawnWave();
}

void PlanesWave::spawnWave(void) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> initX(1180, 1380);
    std::uniform_int_distribution<> initY(100, 620);
    std::uniform_int_distribution<> randomY(-50, 50);
    std::uniform_int_distribution<> randomFrame(0, 7);
    float x = initX(gen);
    float y = initY(gen);

    for (std::size_t i = 0; i < 4; i++) {
        spawnEntity(gengine::component::Transform2D({x, y + randomY(gen)}, {2, 2}, 0),
                    gengine::component::Velocity2D(-PLANE_DEFAULT_SPEED, 0),
                    gengine::component::driver::output::Sprite("r-typesheet5.gif", Rectangle{0, 0, 33, 36}, WHITE),
                    gengine::component::driver::output::Animation("r-typesheet5.json/red_enemy", 0.075f),
                    gengine::component::driver::output::Drawable(1), component::Plane(), component::Monster(),
                    gengine::component::HitBoxSquare2D(32, 36), component::Score(100));
        x += 75;
    }
}
} // namespace rtype::system
