/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Interface.cpp
*/

#include "GEngine/interface/Internal.hpp"

namespace gengine::interface {
Internal::Internal(game::Engine &gameEngine, driver::Engine &driverEngine)
    : m_gameEngine(gameEngine)
    , m_driverEngine(driverEngine) {
}

void Internal::run(void) {
    m_gameEngine.start();
    m_driverEngine.start();
    m_gameEngine.compute();
    m_driverEngine.compute();
}
} // namespace gengine::interface