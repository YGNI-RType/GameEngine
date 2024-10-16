/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** CaterpillarsWave.cpp
*/

#include "systems/CaterpillarsWave.hpp"

#include <random>

namespace rtype::system {
void CaterpillarsWave::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&CaterpillarsWave::onGameLoop);
}

void CaterpillarsWave::onGameLoop(gengine::system::event::GameLoop &e) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> change_spawn_vawe(0, 250);

    if (change_spawn_vawe(gen) == 0)
        spawnWave();
}

void CaterpillarsWave::spawnWave(void) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> initX(1180, 1380);
    std::uniform_int_distribution<> initY(250, 470);
    std::uniform_int_distribution<> randomFrame(0, 7);

    float x = initX(gen);
    float firstY = initY(gen);
    float y = firstY;
    Rectangle rec = {0, 0, 33, 34};
    rec.x = (firstY < 360) ? rec.width * 6 : rec.width * 2;
    rec.y = (firstY < 360) ? 0 : rec.height;
    int direction = (firstY < 360) ? 1 : -1;

    for (std::size_t i = 0; i < 5; i++) {
        spawnEntity(gengine::component::Transform2D({x, y}, {2, 2}, 0),
                    gengine::component::Velocity2D(-CATERPILLAR_DEFAULT_SPEED, CATERPILLAR_DEFAULT_SPEED * direction),
                    gengine::component::driver::output::Sprite("r-typesheet8.gif", rec, WHITE),
                    gengine::component::driver::output::Drawable(1), component::Caterpillar(), component::Monster(),
                    gengine::component::HitBoxSquare2D(rec.width, rec.height), component::Score(100));
        x += 50;
        y += 50 * -direction;
    }
}
} // namespace rtype::system
