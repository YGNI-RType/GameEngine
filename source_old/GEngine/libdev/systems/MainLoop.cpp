/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MainLoop.cpp
*/

#include "GEngine/libdev/systems/MainLoop.hpp"

namespace gengine::system {

AutoMainLoop::AutoMainLoop(void) { m_lastTime = std::chrono::high_resolution_clock::now(); }

double AutoMainLoop::getElapsedTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTime - m_lastTime;
    m_lastTime = currentTime;
    return elapsed.count();
}

void AutoMainLoop::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&AutoMainLoop::onStartEngine);
    subscribeToEvent<gengine::system::event::MainLoop>(&AutoMainLoop::onMainLoop);
    subscribeToEvent<gengine::system::event::StopMainLoop>(&AutoMainLoop::onStopMainLoop);
}

void AutoMainLoop::onStartEngine(gengine::system::event::StartEngine &e) {
    publishEvent(gengine::system::event::MainLoop(0));
}

void AutoMainLoop::onMainLoop(gengine::system::event::MainLoop &e) {
    if (m_isRunning)
        publishEvent(gengine::system::event::MainLoop(getElapsedTime()));
}

void AutoMainLoop::onStopMainLoop(gengine::system::event::StopMainLoop &e) { m_isRunning = false; }

} // namespace gengine::system
