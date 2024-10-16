/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** CaterpillarsBound.cpp
*/

#include "systems/CaterpillarsBound.hpp"

namespace rtype::system {
void CaterpillarsBound::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&CaterpillarsBound::onGameLoop);
}

void CaterpillarsBound::onGameLoop(gengine::system::event::GameLoop &e) {
    auto &motions = getComponents<gengine::component::Velocity2D>();
    auto &transforms = getComponents<gengine::component::Transform2D>();
    auto &sprites = getComponents<gengine::component::driver::output::Sprite>();
    auto &caterpillars = getComponents<component::Caterpillar>();

    for (auto [entity, motion, transform, sprite, caterpillar] :
         gengine::Zip(motions, transforms, sprites, caterpillars)) {
        if (transform.pos.y < 0) {
            motion.y = -motion.y;
            sprite.src.x = sprite.src.width * 6;
            sprite.src.y = 0;
        }
        if (transform.pos.y > 720 - sprite.src.height * 1.5) {
            motion.y = -motion.y;
            sprite.src.x = sprite.src.width * 2;
            sprite.src.y = sprite.src.height;
        }
    }
}
} // namespace rtype::system
