/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Animation.hpp
*/

/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Sprite.hpp
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
