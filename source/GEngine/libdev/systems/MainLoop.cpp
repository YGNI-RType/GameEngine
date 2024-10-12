/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MainLoop.cpp
*/

#include "GEngine/libdev/systems/MainLoop.hpp"

#include <thread>

namespace gengine::system {

AutoMainLoop::AutoMainLoop(int TPS)
    : m_lastTime(std::chrono::high_resolution_clock::now())
    , m_timePerLoop(1000 / 60) {
}

std::chrono::milliseconds AutoMainLoop::getElapsedTime(void) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> elapsed = currentTime - m_lastTime;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
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
    if (!m_isRunning)
        return;
    auto delta = getElapsedTime();
    std::this_thread::sleep_for(m_timePerLoop - delta);
    publishEvent(gengine::system::event::MainLoop((delta > m_timePerLoop ? delta : m_timePerLoop).count()));
    m_lastTime = std::chrono::high_resolution_clock::now();
}

void AutoMainLoop::onStopMainLoop(gengine::system::event::StopMainLoop &e) {
    m_isRunning = false;
}

} // namespace gengine::system
