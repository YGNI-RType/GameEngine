/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** DriverSystem.hpp
*/

#pragma once

#include <memory>

#include "GEngine/driver/systems/Library/Library.hpp"
#include "ecs/system/Base.hpp"

class DriverSystem : public ecs::system::Base<DriverSystem> {
public:
    DriverSystem(ecs::system::event::Bus &eventBus, std::unique_ptr<Library> gLib)
        : Base<DriverSystem>(eventBus) {
        m_gLib = std::move(gLib);
    }

private:
    static std::unique_ptr<Library> m_gLib;
};

std::unique_ptr<Library> DriverSystem::m_gLib = nullptr;
