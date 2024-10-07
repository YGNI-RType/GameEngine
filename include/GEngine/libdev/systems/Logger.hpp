/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Logger.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/Log.hpp"

#include <fstream>

namespace gengine::system {
class Logger : public gengine::System<Logger> {
public:
    Logger(const std::string &filename);

    void init(void) override;

    void onLog(event::Log &e);

private:
    std::ofstream m_logFile;
};
} // namespace gengine::system
