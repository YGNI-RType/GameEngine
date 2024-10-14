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
    AutoMainLoop(size_t fps = 60, size_t tps = 60);

    void init(void) override;

    void onStartEngine(gengine::system::event::StartEngine &e);

    void onMainLoop(gengine::system::event::MainLoop &e);

    void onStopMainLoop(gengine::system::event::StopMainLoop &e);

    std::chrono::microseconds getElapsedTime(void);

private:
    bool m_isRunning = true;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
    std::chrono::microseconds m_driverTime;
    std::chrono::microseconds m_gameTime;
    size_t m_fps;
    size_t m_tps;
};
} // namespace gengine::system
