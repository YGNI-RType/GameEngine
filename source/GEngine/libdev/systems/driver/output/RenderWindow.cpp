/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** RenderWindow.cpp
*/

#include "GEngine/libdev/systems/driver/output/RenderWindow.hpp"
#include <iostream>

namespace gengine::system::driver::output {
RenderWindow::RenderWindow(int width, int height, const std::string &title)
    : m_width(width)
    , m_height(height)
    , m_title(title) {
}

void RenderWindow::init(void) {
    subscribeToEvent<gengine::system::event::StartEngine>(&RenderWindow::onStartEngine);
    subscribeToEvent<gengine::system::event::MainLoop>(&RenderWindow::onMainLoop);
}

void RenderWindow::onStartEngine(gengine::system::event::StartEngine &e) {
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT); // TODO FLAG_WINDOW_RESIZABLE
    InitWindow(m_width, m_height, m_title.c_str());
    SetWindowMonitor(0);
}

void RenderWindow::onMainLoop(gengine::system::event::MainLoop &e) {
    if (WindowShouldClose())
        publishEvent(gengine::system::event::StopMainLoop());

    if (IsWindowResized()) {
        m_width = GetRenderWidth();
        m_height = GetRenderHeight();
    }
}

int RenderWindow::getWidth(void) const {
    return m_width;
}

void RenderWindow::setWidth(int width) {
    m_width = width;
}

int RenderWindow::getHeight(void) const {
    return m_height;
}

void RenderWindow::setHeight(int height) {
    m_height = height;
}

const std::string &RenderWindow::getTitle(void) const {
    return m_title;
}

void RenderWindow::setTitle(const std::string &title) {
    m_title = title;
}
} // namespace gengine::system::driver::output
