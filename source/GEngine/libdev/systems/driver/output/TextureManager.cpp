/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** TextureManager.cpp
*/

#include "GEngine/libdev/systems/driver/output/TextureManager.hpp"

namespace gengine::system::driver::output {
TextureManager::TextureManager(const std::string &folder)
    : m_folder(folder) {
}

void TextureManager::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&TextureManager::onStartEngine);
    subscribeToEvent<gengine::system::event::StopEngine>(&TextureManager::onStopEngine);
}

void TextureManager::onStartEngine(gengine::system::event::StartEngine &e) {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(m_folder)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();

            // Check if the file has a valid image extension
            // if (isValidImageFile(filePath)) {
            Texture texture = LoadTexture(filePath.c_str());
            std::string path = std::filesystem::relative(entry.path(), m_folder).string();
            m_textureTable.emplace(path, texture);
            // }
        }
    }
}

void TextureManager::onStopEngine(gengine::system::event::StopEngine &e) {
    for (auto &[path, texture] : m_textureTable) {
        UnloadTexture(texture);
        // // std::cout << "Unloaded texture: " << path << std::endl; // TODO log
    }
}

const Texture &TextureManager::get(const std::string &path) {
    const auto &texture = m_textureTable.find(path);
    if (texture == m_textureTable.cend())
        THROW_ERROR("Out of range: This texture does not exist.");

    return texture->second;
}
} // namespace gengine::system::driver::output