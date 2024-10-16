/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : SoundManager.hpp
**  Create at   : 2024-10-15 05:02
**  Author      : AUTHOR
**  Description : This system dedicated to ther DriverEngine, it must with
                    the raylib play and manage sounds.
** ═══════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/libdev/systems/events/driver/output/Sound.hpp"

#include "module/raylib_safe.h"

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