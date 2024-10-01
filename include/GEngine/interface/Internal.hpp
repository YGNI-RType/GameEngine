/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Internal.hpp
*/

#pragma once

#include "GEngine/driver/Engine.hpp"
#include "GEngine/game/Engine.hpp"
#include "GEngine/interface/Base.hpp"

namespace gengine::interface {
class Internal : public Base {
public:
    Internal(game::Engine &gameEngine, driver::Engine &driverEngine);

    void run(void) override;

private:
    game::Engine &m_gameEngine;
    driver::Engine &m_driverEngine;
};
} // namespace gengine::interface
