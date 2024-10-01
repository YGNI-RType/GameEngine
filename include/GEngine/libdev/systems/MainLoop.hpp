/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MainLoop.hpp
*/

#pragma once

#include <chrono>

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

namespace gengine::system {
class AutoMainLoop : public gengine::System<AutoMainLoop> {
public:
    AutoMainLoop(void);

    void init(void) override;

    void onStartEngine(gengine::system::event::StartEngine &e);

    void onMainLoop(gengine::system::event::MainLoop &e);

    void onStopMainLoop(gengine::system::event::StopMainLoop &e);

    double getElapsedTime(void);

private:
    bool m_isRunning = true;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
};
} // namespace gengine::system
