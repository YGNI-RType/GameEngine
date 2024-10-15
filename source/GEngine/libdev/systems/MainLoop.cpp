/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** MainLoop.cpp
*/

#include "GEngine/libdev/systems/MainLoop.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "GEngine/libdev/systems/events/RenderLoop.hpp"

#include <thread>

namespace gengine::system {

AutoMainLoop::AutoMainLoop(size_t fps, size_t tps)
    : m_lastTime(std::chrono::high_resolution_clock::now())
    , m_driverTime(1000000 / fps)
    , m_gameTime(1000000 / tps)
    , m_fps(fps)
    , m_tps(tps) {
}

std::chrono::microseconds AutoMainLoop::getElapsedTime(void) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::micro> elapsed = currentTime - m_lastTime;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
}

void AutoMainLoop::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&AutoMainLoop::onStartEngine);
    subscribeToEvent<gengine::system::event::MainLoop>(&AutoMainLoop::onMainLoop);
    subscribeToEvent<gengine::system::event::StopMainLoop>(&AutoMainLoop::onStopMainLoop);
}

void AutoMainLoop::onStartEngine(gengine::system::event::StartEngine &e) {
    publishEvent(gengine::system::event::MainLoop(0));
    m_lastTime = std::chrono::high_resolution_clock::now();
}

void AutoMainLoop::onMainLoop(gengine::system::event::MainLoop &e) {
    if (!m_isRunning)
        return;

    auto delta = getElapsedTime();
    m_driverTime -= delta;
    m_gameTime -= delta;
    if (m_driverTime.count() <= 0) {
        m_driverTime += std::chrono::microseconds(1000000 / m_fps);
        publishEvent<gengine::system::event::RenderLoop>(m_driverTime.count() / 1000.f); // TODO add time if < 0
    }
    if (m_gameTime.count() <= 0) {
        m_gameTime += std::chrono::microseconds(1000000 / m_tps);
        publishEvent<gengine::system::event::GameLoop>(m_gameTime.count() / 1000.f); // TODO add time if < 0
    }
    publishEvent(gengine::system::event::MainLoop(delta.count() / 1000.f));
    m_lastTime = std::chrono::high_resolution_clock::now();

    std::this_thread::sleep_for(std::chrono::microseconds(10));
}

void AutoMainLoop::onStopMainLoop(gengine::system::event::StopMainLoop &e) {
    m_isRunning = false;
}

} // namespace gengine::system
