/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** main.cpp
*/

#include "GEngine/driver/Engine.hpp"
#include "GEngine/game/Engine.hpp"
#include "GEngine/interface/network/Networked.hpp"

#include "GEngine/libdev/components/HitBoxs.hpp"
// #include "libdev/components/Positions.hpp"

#include "GEngine/libdev/systems/Collisions.hpp"
#include "GEngine/libdev/systems/MainLoop.hpp"

#include "GEngine/libdev/components/Velocities.hpp"
#include "GEngine/libdev/systems/Collisions.hpp"
#include "GEngine/libdev/systems/Logger.hpp"
// #include "libdev/components/Positions.hpp"

#include "GEngine/libdev/systems/Collisions.hpp"
#include "GEngine/libdev/systems/Logger.hpp"
#include "GEngine/libdev/systems/MainLoop.hpp"
#include "GEngine/libdev/systems/Motions.hpp"

#include "GEngine/libdev/systems/Motions.hpp"

#include "GEngine/libdev/systems/Collisions.hpp"
#include "GEngine/libdev/systems/Logger.hpp"
#include "GEngine/libdev/systems/MainLoop.hpp"
#include "GEngine/libdev/systems/Motions.hpp"

#include "GEngine/libdev/systems/events/Log.hpp"

#include "systems/AutoMotion.hpp"
#include "systems/Start.hpp"

#include "GEngine/libdev/systems/driver/input/KeyboardCatcher.hpp"
#include "GEngine/libdev/systems/driver/input/MouseCatcher.hpp"
#include "GEngine/libdev/systems/driver/output/Animate.hpp"
#include "GEngine/libdev/systems/driver/output/Draw.hpp"
#include "GEngine/libdev/systems/driver/output/RenderWindow.hpp"
#include "GEngine/libdev/systems/driver/output/TextureManager.hpp"

#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"

#include <random>

class Killer : public gengine::System<Killer, gengine::component::Transform2D, gengine::component::HitBoxSquare2D> {
public:
    void init(void) override {
        subscribeToEvent<gengine::system::event::Collsion>(&Killer::onCollision);
        subscribeToEvent<gengine::system::event::driver::input::Mouse_Left>(&Killer::onClickLeft);
    }

    void onClickLeft(gengine::system::driver::input::MouseLeftEvent &e) {
        auto &transforms = getComponents<gengine::component::Transform2D>();
        auto &hitboxes = getComponents<gengine::component::HitBoxSquare2D>();
        for (auto &[entity, transf] : transforms) {
            if (hitboxes.contains(entity)) {
                auto &hitbox = hitboxes.get(entity);
                if (e.cursorPos.x >= transf.pos.x && e.cursorPos.y >= transf.pos.y &&
                    e.cursorPos.x <= transf.pos.x + hitbox.width * transf.scale.x &&
                    e.cursorPos.y <= transf.pos.y + hitbox.height * transf.scale.y)
                    killEntity(entity);
            }
        }
    }
    void onCollision(gengine::system::event::Collsion &e) {
        // auto &colors = getComponents<gengine::component::driver::output::Color>();
        // std::string logMessage = "Receive collision between (" + std::to_string(e.entity1) + ") and (" +
        // std::to_string(e.entity2) + ").";

        // publishEvent(gengine::system::event::Log(logMessage));
        // if (e.entity1 && e.entity2)
        //     return;
        // if (e.entity1)
        //     colors.get(e.entity1).color = GREEN;
        // if (e.entity2)
        //     colors.get(e.entity2).color = GREEN;
    }
};

int main(void) {
    gengine::game::Engine gameEngine;
    gengine::driver::Engine driverEngine;

    // Components
    // gameEngine.registerComponent<gengine::component::HitBoxCircle2D>();
    // gameEngine.registerComponent<gengine::component::HitBoxSquare2D>();
    gameEngine.registerComponent<gengine::component::Transform2D>();
    gameEngine.registerComponent<gengine::component::Velocity2D>();

    gameEngine.registerComponent<gengine::component::driver::output::Animation>();
    gameEngine.registerComponent<gengine::component::driver::output::Drawable>();
    // gameEngine.registerComponent<gengine::component::driver::output::Rectangle>();
    // gameEngine.registerComponent<gengine::component::driver::output::Circle>();
    gameEngine.registerComponent<gengine::component::driver::output::Sprite>();
    gameEngine.registerComponent<gengine::component::driver::output::Text>();

    // Systems
    // customs
    gameEngine.registerSystem<gengine::system::AutoMainLoop>();

    gameEngine.registerSystem<gengine::system::driver::output::RenderWindow>(1080, 720, "hagar");
    gameEngine.registerSystem<gengine::system::driver::output::Draw2D>();
    gameEngine.registerSystem<gengine::system::driver::output::DrawSprite>();
    gameEngine.registerSystem<gengine::system::driver::output::DrawText>();
    gameEngine.registerSystem<gengine::system::driver::output::Animate>();
    gameEngine.registerSystem<gengine::system::driver::output::TextureManager>("../sprites");
    gameEngine.registerSystem<gengine::system::driver::output::FontManager>("../font");

    gameEngine.registerSystem<hagarioop::systems::Start>();
    gameEngine.registerSystem<gengine::system::Motion2D>();
    // gameEngine.registerSystem<gengine::system::Collision2D>();
    gameEngine.registerSystem<hagarioop::systems::AutoMotion>();
    gameEngine.registerSystem<gengine::system::driver::input::KeyboardCatcher>();
    // gameEngine.registerSystem<gengine::system::driver::input::MouseCatcher>();

    // gameEngine.registerSystem<ChangeColor>();
    // gameEngine.registerSystem<gengine::system::Logger>("ECS.log");
    // gameEngine.registerSystem<ChangeColor>();
    // gameEngine.registerSystem<gengine::system::Logger>("ECS.log");

    gengine::interface::network::Networked interface(gameEngine, driverEngine);
    interface.run();
}
