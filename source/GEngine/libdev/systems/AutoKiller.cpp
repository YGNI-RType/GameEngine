/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** AutoKiller.cpp
*/

#include "GEngine/libdev/systems/AutoKiller.hpp"

namespace gengine::system {

void AutoKiller::init(void) {
    subscribeToEvent<event::GameLoop>(&AutoKiller::onGameLoop);
}

void AutoKiller::onGameLoop(event::GameLoop &e [[maybe_unused]]) {
    auto &spanlifes = getComponents<component::SpanLife>();

    for (auto &[entity, spanlife] : spanlifes) {
        spanlife.time -= e.deltaTime / 1000.f;
        if (spanlife.time < 0)
            killEntity(entity);
    }
}
} // namespace gengine::system
