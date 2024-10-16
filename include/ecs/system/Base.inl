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

template <class Derived, class... DependTypes>
template <typename EventType>
void Base<Derived, DependTypes...>::subscribeToEvent(std::function<void(EventType &)> callback) {
    m_eventBus->get().template subscribe<EventType>(callback);
}

template <class Derived, class... DependTypes>
template <typename T>
T &Base<Derived, DependTypes...>::getSystem(void) {
    static_assert(is_one_of<T, DependTypes...>::value, "SystemType is not in the list of allowed types");
    return m_ecs->get().template getSystem<T>();
}

template <class Derived, class... DependTypes>
template <typename T>
component::SparseArray<T> &Base<Derived, DependTypes...>::getComponents(void) {
    static_assert(is_one_of<T, DependTypes...>::value, "ComponentType is not in the list of allowed types");
    return m_ecs->get().template getComponents<T>();
}

template <class Derived, class... DependTypes>
template <class T>
void Base<Derived, DependTypes...>::setComponent(entity::Entity entity, const T &component) {
    static_assert(is_one_of<T, DependTypes...>::value, "ComponentType is not in the list of allowed types");
    m_ecs->get().template setComponent<T>(entity, component);
}

template <class Derived, class... DependTypes>
template <class T, class... Params>
void Base<Derived, DependTypes...>::setComponent(entity::Entity entity, Params &&...p) {
    static_assert(is_one_of<T, DependTypes...>::value, "ComponentType is not in the list of allowed types");
    m_ecs->get().template setComponent<T>(entity, std::forward<Params>(p)...);
}

template <class Derived, class... DependTypes>
void Base<Derived, DependTypes...>::setComponent(entity::Entity entity, const std::type_index &type,
                                                 const std::any &component) {
    m_ecs->get().setComponent(entity, type, component);
}

template <class Derived, class... DependTypes>
template <class T>
void Base<Derived, DependTypes...>::unsetComponent(entity::Entity entity) {
    static_assert(is_one_of<T, DependTypes...>::value, "ComponentType is not in the list of allowed types");
    m_ecs->get().template unsetComponent<T>(entity);
}

template <class Derived, class... DependTypes>
void Base<Derived, DependTypes...>::unsetComponent(entity::Entity entity, const std::type_index &type) {
    m_ecs->get().unsetComponent(entity, type);
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

template <class Derived, class... DependTypes>
void Base<Derived, DependTypes...>::killEntity(entity::Entity entity) {
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

template <class Derived, class... DependTypes>
void Base<Derived, DependTypes...>::pause(void) {
    m_isRunning = false;
}

template <class Derived, class... DependTypes>
void Base<Derived, DependTypes...>::resume(void) {
    m_isRunning = true;
}

template <class Derived, class... DependTypes>
ecs::component::ComponentTools::component_id_t
Base<Derived, DependTypes...>::getComponentId(const std::type_index &type) const {
    return m_ecs->get().getComponentId(type);
}

template <class Derived, class... DependTypes>
const std::type_index &
Base<Derived, DependTypes...>::getTypeindex(ecs::component::ComponentTools::component_id_t id) const {
    return m_ecs->get().getTypeindex(id);
}

template <class Derived, class... DependTypes>
ecs::component::ComponentTools::component_size_t
Base<Derived, DependTypes...>::getComponentSize(const std::type_index &type) const {
    return m_ecs->get().getComponentSize(type);
}
template <class Derived, class... DependTypes>
std::vector<ecs::component::component_info_t>
Base<Derived, DependTypes...>::compareComponents(const std::type_index &type, const std::any &any1,
                                                 const std::any &any2) const {
    return m_ecs->get().compareComponents(type, any1, any2);
}

template <class Derived, class... DependTypes>
const void *Base<Derived, DependTypes...>::toVoid(const std::type_index &type, const std::any &any) const {
    return m_ecs->get().toVoid(type, any);
}

template <class Derived, class... DependTypes>
const std::any Base<Derived, DependTypes...>::toAny(const std::type_index &type, const void *component) const {
    return m_ecs->get().toAny(type, component);
}
} // namespace ecs::system