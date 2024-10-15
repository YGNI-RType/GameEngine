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

    auto &animMan = getSystem<AnimationManager>();
    for (auto [entity, anim, sprite] : Zip(animations, sprites)) {
        anim.currentTime += e.deltaTime / 1000.f;
        if (anim.currentTime < anim.frameDuration)
            continue;
        anim.currentTime -= anim.frameDuration; // while ?
        auto &track = animMan.getAnimationTrack(anim.trackName);
        int currentframe = track.frames[anim.currentFrameIndex];
        switch (anim.getPlaybackMode()) {
        case ATrack::PlaybackMode::Forward:
            if (anim.currentFrameIndex == track.frames.size() - 1)
                if (track.looping)
                    anim.currentFrameIndex = 0;
                else
                    anim.currentFrameIndex = track.frames.size() - 1;
            else
                anim.currentFrameIndex++;
            break;
        case ATrack::PlaybackMode::Reverse:
            if (anim.currentFrameIndex == 0)
                if (track.looping)
                    anim.currentFrameIndex = track.frames.size() - 1;
                else
                    anim.currentFrameIndex = 0;
            else
                anim.currentFrameIndex--;
            break;
        case ATrack::PlaybackMode::Idling:
            if (anim.currentFrameIndex < track.idleFrameIdx)
                anim.currentFrameIndex++;
            else if (anim.currentFrameIndex > track.idleFrameIdx)
                anim.currentFrameIndex--;
            break;
        default:
            break;
        }

        int delta = track.frames[anim.currentFrameIndex] - currentframe;
        sprite.src.x += delta * sprite.src.width;
    }
}

} // namespace gengine::system::driver::output
