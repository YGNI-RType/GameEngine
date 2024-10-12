/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** FontManager.cpp
*/

#include "GEngine/libdev/systems/driver/output/FontManager.hpp"

namespace gengine::system::driver::output {
FontManager::FontManager(const std::string &folder)
    : m_folder(folder) {
}

void FontManager::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&FontManager::onStartEngine);
    subscribeToEvent<gengine::system::event::StopEngine>(&FontManager::onStopEngine);
}

void FontManager::onStartEngine(gengine::system::event::StartEngine &e) {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(m_folder)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();

            // Check if the file has a valid image extension
            // if (isValidImageFile(filePath)) {
            std::string path = std::filesystem::relative(entry.path(), m_folder).string();
            m_fontTable.emplace(path, LoadFont(filePath.c_str()));
            // }
        }
    }
}

void FontManager::onStopEngine(gengine::system::event::StopEngine &e) {
    for (auto &[path, font] : m_fontTable) {
        UnloadFont(font);
        // // std::cout << "Unloaded Font: " << path << std::endl; // TODO log
    }
}

const Font &FontManager::get(const std::string &path) {
    const auto &font = m_fontTable.find(path);
    if (font == m_fontTable.cend())
        throw std::out_of_range("This font does not exist");

    return font->second;
}
} // namespace gengine::system::driver::output