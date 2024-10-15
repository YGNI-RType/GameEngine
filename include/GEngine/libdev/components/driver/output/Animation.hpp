/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Component
** ════════════════════════════════════════════════════════════════════════════
**  File        : Animation.hpp
**  Create at   : 2024-10-15 05:25
**  Auteur      : AUTHOR
**  Description : DESCRIPTION // TODO popoche
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include <raylib.h>

#include "GEngine/libdev/Component.hpp"

namespace gengine::component::driver::output {
struct Animation : public Component<Animation> {
    int nbFrames;        // Total number of frames in the animation
    int currentFrame;    // The current frame of the animation
    float frameDuration; // Time each frame is displayed (in seconds)
    float currentTime;   // Accumulated time used to track when to switch frames
    bool looping;        // Should the animation loop?

    Animation(int nbFrames, int currentFrame, float frameDuration, bool looping = true)
        : nbFrames(nbFrames)
        , currentFrame(0)
        , frameDuration(frameDuration)
        , currentTime(currentFrame * frameDuration)
        , looping(looping) {
    }

    bool operator==(const Animation &) const = default;
};
} // namespace gengine::component::driver::output
