/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Start.hpp
*/

#include "Start.hpp"

#include "GEngine/libdev/components/HitBoxs.hpp"
#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/Velocities.hpp"

#include "GEngine/libdev/components/driver/output/Animation.hpp"
// #include "GEngine/libdev/components/driver/output/Color.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/components/driver/output/Text.hpp"

#include <random>

namespace hagarioop::systems {
void Start::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&Start::onStartEngine);
}

void Start::onStartEngine(gengine::system::event::StartEngine &e) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> entitys_fork(1, 50000);
    std::uniform_int_distribution<> Transformx_fork(0, 1920);
    std::uniform_int_distribution<> Transformy_fork(0, 1080);
    std::uniform_int_distribution<> side_fork(20, 100);
    std::uniform_int_distribution<> motion_fork(-50, 50);

    spawnEntity(gengine::component::Transform2D({0, 0}, {5, 5}, 0), gengine::component::Velocity2D(1, 0),
                // gengine::component::HitBoxCircle2D(100),
                // gengine::component::driver::output::Text("arial.ttf", "Bnjour"),
                gengine::component::driver::output::Drawable(15),
                // gengine::component::driver::output::Sprite("r-typesheet1.gif", Rectangle{101, 0, 33, 17}, WHITE)
                gengine::component::driver::output::Rectangle(100, 5, RED)
                // gengine::component::driver::output::Animation(5, 0, 0.1f)
    );

    // for (std::size_t i = 0; i < 5; i++) {
    //     int side = side_fork(gen);
    //     float x = Transformx_fork(gen);
    //     float y = Transformy_fork(gen);
    //     spawnEntity(gengine::component::Transform2D({x, y}, {5, 5}, 0),
    //                 gengine::component::Velocity2D(motion_fork(gen), motion_fork(gen)),
    //                 // gengine::component::HitBoxSquare2D(side, side),
    //                 // // gengine::component::driver::output::Color(RED),
    //                 gengine::component::driver::output::Rectangle(side, side, RED),
    //                 // gengine::component::driver::output::Sprite("r-typesheet3.gif", Rectangle{0, 0, 17, 18}, WHITE),
    //                 // gengine::component::driver::output::Animation(12, rand() % 12, 0.1f),
    //                 gengine::component::driver::output::Drawable(10));
    //     // spawnEntity(gengine::component::Transform2D({x, y}, {5, 5}, 0),
    //     //             // gengine::component::Velocity2D(motion_fork(gen), motion_fork(gen)),
    //     //             // gengine::component::HitBoxSquare2D(side, side),
    //     //             // // gengine::component::driver::output::Color(RED),
    //     //             // gengine::component::driver::output::Rectangle(side, side, RED)
    //     //             gengine::component::driver::output::Text("arial.ttf", "caca"),
    //     //             gengine::component::driver::output::Animation(12, 10, 0.1f),
    //     //             gengine::component::driver::output::Drawable(11));
    // }
}
} // namespace hagarioop::systems