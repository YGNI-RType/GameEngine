/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : Animate.hpp
**  Create at   : 2024-10-15 05:00
**  Author      : AUTHOR
**  Description : DESCRIPTION // TODO popoche
** ═══════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "GEngine/libdev/components/driver/output/Animation.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace gengine::system::driver::output {
using ATrack = component::driver::output::AnimationTrack;
class AnimationManager : public gengine::System<AnimationManager> {
public:
    AnimationManager(const std::string &folder);

    void init(void) override;

    void onStartEngine(gengine::system::event::StartEngine &e);

    const ATrack getAnimationTrack(const std::string &name) const;

    void loadFromConfig(const std::string &fileName, const json &jsonData);

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