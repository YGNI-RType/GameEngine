/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Networked.hpp
*/

#pragma once

#include "GEngine/driver/Engine.hpp"
#include "GEngine/game/Engine.hpp"
#include "GEngine/interface/Base.hpp"
#include "GEngine/interface/network/systems/Snapshot.hpp"

namespace gengine::interface::network {
class Networked : public Base {
public:
    Networked(game::Engine &gameEngine, driver::Engine &driverEngine)
        : m_gameEngine(gameEngine)
        , m_driverEngine(driverEngine) {
        m_gameEngine.registerSystem<system::Snapshot>(gameEngine.getWorld());
    }

    void run(void) override {
        m_gameEngine.start();
        m_driverEngine.start();
        m_gameEngine.compute();
        m_driverEngine.compute();
    }

private:
    game::Engine &m_gameEngine;
    driver::Engine &m_driverEngine;

    // SnapshotManager m_snapshotMan;
};
} // namespace gengine::interface::network
