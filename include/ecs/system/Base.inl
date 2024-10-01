/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Base.inl
*/

#pragma once

namespace ecs::system {
template <class Derived, class... DependTypes>
template <typename EventType>
void Base<Derived, DependTypes...>::subscribeToEvent(void (Derived::*callbackMethod)(EventType &)) {
    m_eventBus->get().template subscribe<EventType>([this, callbackMethod](EventType &e) -> void {
        if (m_isRunning)
            (static_cast<Derived *>(this)->*callbackMethod)(e);
    });
}

template <class Derived, class... DependTypes> template <typename T> T &Base<Derived, DependTypes...>::getSystem(void) {
    static_assert(is_one_of<T, DependTypes...>::value, "SystemType is not in the list of allowed types");
    return m_ecs->get().template getSystem<T>();
}

template <class Derived, class... DependTypes>
template <typename T>
component::SparseArray<T> &Base<Derived, DependTypes...>::getComponent(void) {
    static_assert(is_one_of<T, DependTypes...>::value, "ComponentType is not in the list of allowed types");
    return m_ecs->get().template getComponents<T>();
}

template <class Derived, class... DependTypes>
template <class T, class... Params>
void Base<Derived, DependTypes...>::registerSystem(Params &&...p) {
    m_ecs->get().template registerSystem<T>(std::forward(p)...);
}

template <class Derived, class... DependTypes>
template <class T>
void Base<Derived, DependTypes...>::registerComponent(void) {
    m_ecs->get().template registerComponent<T>();
}

template <class Derived, class... DependTypes>
template <typename... Components>
void Base<Derived, DependTypes...>::spawnEntity(Components &&...components) {
    m_ecs->get().spawnEntity(std::forward<Components>(components)...);
}

template <class Derived, class... DependTypes> void Base<Derived, DependTypes...>::killEntity(entity::Entity entity) {
    m_ecs->get().killEntity(entity);
}

template <class Derived, class... DependTypes>
template <typename T>
void Base<Derived, DependTypes...>::publishEvent(T &event) {
    m_eventBus->get().template publish<T>(event);
}

template <class Derived, class... DependTypes>
template <typename T>
void Base<Derived, DependTypes...>::publishEvent(T &&event) {
    m_eventBus->get().template publish<T>(event);
}

template <class Derived, class... DependTypes> void Base<Derived, DependTypes...>::pause(void) { m_isRunning = true; }

template <class Derived, class... DependTypes> void Base<Derived, DependTypes...>::resume(void) { m_isRunning = true; }
} // namespace ecs::system