/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** Updater.hpp
*/

#pragma once

#include <array>
#include <functional>

#include "GEngine/BaseEngine.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/MainLoop.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#include "GEngine/interface/network/systems/NetworkComponent.hpp"

namespace gengine::interface::network::system {

class Updater : public System<Updater> {
public:
    Updater(void) = default;
    void init(void) override;
    // void onStartEngine(gengine::system::event::StartEngine &);
    void onMainLoop(gengine::system::event::MainLoop &);

private:
    // std::vector<std::type_index> m_typeTable; // TODO opti
};
} // namespace gengine::interface::network::system