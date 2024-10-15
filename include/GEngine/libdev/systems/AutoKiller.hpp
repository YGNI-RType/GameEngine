/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** AutoKiller.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/SpanLife.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"

namespace gengine::system {
class AutoKiller : public System<AutoKiller, component::SpanLife> {
public:
    void init(void) override;
    void onGameLoop(event::GameLoop &);
};
} // namespace gengine::system