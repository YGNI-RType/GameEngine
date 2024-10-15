/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : Logger.hpp
**  Create at   : 2024-10-15 05:06
**  Author      : AUTHOR
**  Description : This system dedicated to the GameEngine and the DriverEngine
                    allows to produce a log file filled in reaction to the Log
                    event.
** ═══════════════════════════════════════════════════════════════════════════
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
