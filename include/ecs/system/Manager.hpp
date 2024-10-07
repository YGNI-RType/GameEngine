/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** SystemManager.hpp
*/

#pragma once

#include <any>
#include <functional>
#include <memory>
#include <optional>
#include <typeindex>
#include <unordered_map>

#include "ecs/system/IsSystem.hpp"
#include "ecs/system/event/Bus.hpp"
#include "exceptions/Base.hpp"

#include "IsSystem.hpp"

namespace ecs {
class ECS;
}
namespace ecs::system {
class Manager {
public:
    Manager(ECS &ecs)
        : m_ecs(ecs)
        , m_eventBus() {
    }

    template <class T, class... Params>
    void registerSystem(Params &&...p);

    template <class T>
    T &getSystem(void);

    template <class T>
    void publishEvent(T &event);

    template <class T>
    void publishEvent(T &&event);

    void executeEvent(void);

    bool hasEvent(void);

private:
    std::unordered_map<std::type_index, std::unique_ptr<IsSystem>> m_systemTable;
    event::Bus m_eventBus;
    ECS &m_ecs;
};
} // namespace ecs::system

#include "Manager.inl"
