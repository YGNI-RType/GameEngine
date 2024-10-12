/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** system::Base.hpp
*/

#pragma once

#include <functional>

#include "ecs/ECS.hpp"
#include "ecs/system/IsSystem.hpp"
#include "ecs/system/event/Bus.hpp"

namespace ecs::system {
template <typename T, typename... Types>
struct is_one_of;

template <typename T, typename First, typename... Rest>
struct is_one_of<T, First, Rest...>
    : std::conditional_t<std::is_same_v<T, First>, std::true_type, is_one_of<T, Rest...>> {};

template <typename T>
struct is_one_of<T> : std::false_type {};

class Manager;
template <class Derived, class... DependTypes>
class Base : public IsSystem {
public:
    Base() = default;

    virtual ~Base() = default;

    virtual void init(void) = 0;

    template <typename EventType>
    void subscribeToEvent(void (Derived::*callbackMethod)(EventType &));

    template <typename EventType>
    void subscribeToEvent(std::function<void(EventType &)> callback);

    template <typename T>
    T &getSystem(void);

    template <typename T>
    component::SparseArray<T> &getComponents(void);

    template <typename T>
    void setComponent(entity::Entity entity, const T &component);
    template <typename T, class... Params>
    void setComponent(entity::Entity entity, Params &&...p);
    void setComponent(entity::Entity entity, const std::type_index &type, const std::any &comp);

    template <typename T>
    void unsetComponent(entity::Entity entity);
    void unsetComponent(entity::Entity entity, const std::type_index &type);

    template <class T, class... Params>
    void registerSystem(Params &&...p);

    template <class T>
    void registerComponent(void);

    template <typename... Components>
    void spawnEntity(Components &&...components);

    void killEntity(entity::Entity entity);

    template <typename T>
    void publishEvent(T &event);

    template <typename T>
    void publishEvent(T &&event);

    void pause(void);

    void resume(void);

    ecs::component::ComponentTools::component_id_t getComponentId(const std::type_index &type) const;
    const std::type_index &getTypeindex(ecs::component::ComponentTools::component_id_t id) const;
    ecs::component::ComponentTools::component_size_t getComponentSize(const std::type_index &type) const;
    std::vector<ecs::component::component_info_t> compareComponents(const std::type_index &type, const std::any &any1,
                                                                    const std::any &any2) const;
    const void *toVoid(const std::type_index &type, const std::any &any) const;
    const std::any toAny(const std::type_index &type, const void *component) const;

private:
    friend class system::Manager;

    std::optional<std::reference_wrapper<ECS>> m_ecs;
    std::optional<std::reference_wrapper<event::Bus>> m_eventBus;
    bool m_isRunning = true;
};
} // namespace ecs::system

#include "Base.inl"
