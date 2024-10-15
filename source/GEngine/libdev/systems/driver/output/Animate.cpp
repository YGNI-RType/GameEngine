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

AnimationManager::AnimationManager(const std::string &folder)
    : m_folder(folder) {
}

void AnimationManager::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&AnimationManager::onStartEngine);
}

void AnimationManager::onStartEngine(gengine::system::event::StartEngine &e) {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(m_folder)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();

            std::string path = std::filesystem::relative(entry.path(), m_folder).string();
            std::ifstream inputFile(filePath);
            if (!inputFile.is_open()) {
                std::cerr << "Could not open the file: " << filePath << std::endl;
                return;
            }
            json jsonData;
            inputFile >> jsonData;
            inputFile.close();
            loadFromConfig(path, jsonData);
        }
    }
}
const ATrack AnimationManager::getAnimationTrack(const std::string &name) const {
    auto it = m_trackMap.find(name);
    if (it == m_trackMap.end())
        THROW_ERROR("This animation is not in the AnimationManager");
    return it->second;
}

void AnimationManager::loadFromConfig(const std::string &fileName, const json &jsonData) {
    for (auto &[key, value] : jsonData.items()) {
        std::vector<int> frames = value["frames"].get<std::vector<int>>();

        size_t idleFrameIdx = value.contains("idleFrameIdx") ? value["idleFrameIdx"].get<size_t>() : 0;

        bool looping = value.contains("looping") ? value["looping"].get<bool>() : true;

        m_trackMap.emplace(fileName + '/' + key, ATrack(frames, idleFrameIdx, looping));
    }
}
} // namespace gengine::system::driver::output
