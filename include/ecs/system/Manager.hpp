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
        , m_eventBus()
        , m_systemTable() {
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

    template <typename Type>
    void subscribeCallback(std::function<void(Type &)> callback) {
        m_eventBus.subscribe<Type>(callback);
    }

private:
    ECS &m_ecs;
    event::Bus m_eventBus;
    std::unordered_map<std::type_index, std::unique_ptr<IsSystem>> m_systemTable = {};
};
} // namespace ecs::system

#include "Manager.inl"
