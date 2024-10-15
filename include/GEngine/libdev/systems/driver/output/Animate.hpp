/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Animate.hpp
*/

#pragma once

#include <filesystem>
#include <unordered_map>

#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

// #include <nlohmann/json.hpp>
// TODO using json = nlohmann::json;

namespace gengine::system::driver::output {
using ATrack = component::driver::output::AnimationTrack;
class AnimationManager : public gengine::System<AnimationManager> {
public:
    AnimationManager(const std::string &folder)
        : m_folder(folder) {
    }

    void init(void) override {
        subscribeToEvent<gengine::system::event::StartEngine>(&AnimationManager::onStartEngine);
    }

    void onStartEngine(gengine::system::event::StartEngine &e) {
        for (const auto &entry : std::filesystem::recursive_directory_iterator(m_folder)) {
            if (entry.is_regular_file()) {
                std::string filePath = entry.path().string();

                // TODO Check if the file has a valid image extension
                std::string path = std::filesystem::relative(entry.path(), m_folder).string();
                loadFromConfig(path);
            }
        }
    }
    const ATrack getAnimationTrack(const std::string &name) const {
        auto it = m_trackMap.find(name);
        if (it == m_trackMap.end())
            THROW_ERROR("This animation is not in the AnimationManager");
        return it->second;
    }

    void loadFromConfig(const std::string &configFile) {
        // Load animation data from the file into the trackMap
        // TODO
        ATrack spaceship({0, 1, 2, 3, 4}, 2, false);
        m_trackMap.insert({configFile + "/spaceship", spaceship}); // examples
        ATrack enemy({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
        m_trackMap.insert({configFile + "/enemy", enemy});
        /*

        Example: see assets/animations
        */
    }

private:
    std::string m_folder;
    std::unordered_map<std::string, ATrack> m_trackMap;
};

class Animate : public System<Animate, component::driver::output::Sprite, component::driver::output::Animation,
                              AnimationManager> {
public:
    void init(void) override;

    void onGameLoop(gengine::system::event::GameLoop &e);
private:
};
} // namespace gengine::system::driver::output