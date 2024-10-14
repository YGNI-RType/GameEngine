/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Sound.hpp
*/

#pragma once

#include "GEngine/libdev/Entity.hpp"
#include "GEngine/libdev/System.hpp"

namespace gengine::system::event::driver::output {
class Sound : public Event {
public:
    Sound(const std::string &path)
        : m_path(path) {
    }

    const std::string &getPath(void) const {
        return m_path;
    }

private:
    const std::string m_path;
};
} // namespace gengine::system::event::driver::output
