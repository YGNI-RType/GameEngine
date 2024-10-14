/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** SoundManager.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/libdev/systems/events/driver/output/Sound.hpp"

#include <raylib.h>

#include <filesystem>

namespace gengine::system::driver::output {
class SoundManager : public gengine::System<SoundManager> {
public:
    SoundManager(const std::string &folder);
    void init(void) override;

    void onStartEngine(gengine::system::event::StartEngine &e);
    void onStopEngine(gengine::system::event::StopEngine &e);
    void onSound(gengine::system::event::driver::output::Sound &e);

    const Sound &get(const std::string &path);

private:
    std::string m_folder;
    std::unordered_map<std::string, Sound> m_soundTable;
};
} // namespace gengine::system::driver::output