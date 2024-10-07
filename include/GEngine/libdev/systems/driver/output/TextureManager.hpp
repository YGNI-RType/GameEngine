/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** TextureManager.hpp
*/

#pragma once

#include <filesystem>
#include <raylib.h>
#include <unordered_map>

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

namespace gengine::system::driver::output {
class TextureManager : public gengine::System<TextureManager> {
public:
    TextureManager(const std::string &folder);
    void init(void) override;

    void onStartEngine(gengine::system::event::StartEngine &e);
    void onStopEngine(gengine::system::event::StopEngine &e);

    const Texture &get(const std::string &path);

private:
    std::string m_folder;
    std::unordered_map<std::string, Texture> m_textureTable;
};
} // namespace gengine::system::driver::output