/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** FontManager.hpp
*/

#pragma once

#include <filesystem>
#include <raylib.h>
#include <unordered_map>

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

namespace gengine::system::driver::output {
class FontManager : public gengine::System<FontManager> {
public:
    FontManager(const std::string &folder);
    void init(void) override;

    void onStartEngine(gengine::system::event::StartEngine &e);
    void onStopEngine(gengine::system::event::StopEngine &e);

    const Font &get(const std::string &path);

private:
    std::string m_folder;
    std::unordered_map<std::string, Font> m_fontTable;
};
} // namespace gengine::system::driver::output