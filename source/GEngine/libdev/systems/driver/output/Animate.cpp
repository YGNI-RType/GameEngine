/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Animate.cpp
*/

#include "GEngine/libdev/systems/driver/output/Animate.hpp"

namespace gengine::system::driver::output {
void Animate::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&Animate::onGameLoop);
}

void Animate::onGameLoop(gengine::system::event::GameLoop &e) {
    auto &animations = getComponents<component::driver::output::Animation>();
    auto &sprites = getComponents<component::driver::output::Sprite>();

    for (auto [entity, anim, sprite] : Zip(animations, sprites)) {
        anim.currentTime += e.deltaTime / 1000.f;
        int newFrame = anim.currentTime / anim.frameDuration;
        if (!(newFrame - anim.currentFrame))
            continue;
        if (newFrame >= anim.nbFrames) {
            if (anim.looping) {
                newFrame %= anim.nbFrames;
                anim.currentTime = 0.f;
            } else {
                newFrame = anim.nbFrames - 1;
            }
        }
        int delta = newFrame - anim.currentFrame;

        sprite.src.x += delta * sprite.src.width;

        anim.currentFrame = newFrame;
    }
}
} // namespace gengine::system::driver::output
