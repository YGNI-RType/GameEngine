/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Logger.cpp
*/

#include "GEngine/libdev/systems/Logger.hpp"

namespace gengine::system {
Logger::Logger(const std::string &filename)
    : m_logFile(filename, std::ios::app) {
}

void Logger::init(void) {
    subscribeToEvent<event::Log>(&Logger::onLog);
}

void Logger::onLog(event::Log &e) {
    m_logFile << e.message << std::endl;
}
} // namespace gengine::system
