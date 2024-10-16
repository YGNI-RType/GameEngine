/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** SoundManager.cpp
*/

#include "GEngine/libdev/systems/driver/output/SoundManager.hpp"

namespace gengine::system::driver::output {
SoundManager::SoundManager(const std::string &folder)
    : m_folder(folder) {
}

void SoundManager::init(void) {
    InitAudioDevice();
    subscribeToEvent<gengine::system::event::StartEngine>(&SoundManager::onStartEngine);
    subscribeToEvent<gengine::system::event::StopEngine>(&SoundManager::onStopEngine);
    subscribeToEvent<gengine::system::event::driver::output::Sound>(&SoundManager::onSound);
}

void SoundManager::onStartEngine(gengine::system::event::StartEngine &e) {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(m_folder)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();

            // Check if the file has a valid image extension
            // if (isValidImageFile(filePath)) {
            Sound sound = LoadSound(filePath.c_str());
            std::string path = std::filesystem::relative(entry.path(), m_folder).string();
            m_soundTable.emplace(path, sound);
            // }
        }
    }
}

void SoundManager::onStopEngine(gengine::system::event::StopEngine &e) {
    for (auto &[path, sound] : m_soundTable) {
        UnloadSound(sound);
        // // std::cout << "Unloaded texture: " << path << std::endl; // TODO log
    }
}

const Sound &SoundManager::get(const std::string &path) {
    const auto &sound = m_soundTable.find(path);
    if (sound == m_soundTable.cend())
        THROW_ERROR("Out of range: This sound does not exist.");

    return sound->second;
}

void SoundManager::onSound(gengine::system::event::driver::output::Sound &e) {
    PlaySound(get(e.getPath()));
}
} // namespace gengine::system::driver::output