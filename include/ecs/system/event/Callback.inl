/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Callback.inl
*/

#pragma once

namespace ecs::system::event {

template <typename T, typename Type>
MethodCallback<T, Type>::MethodCallback(T &instance, CallbackMethod callbackMethod)
    : m_instance(instance)
    , m_callbackMethod(callbackMethod) {
}

template <typename T, typename Type>
void MethodCallback<T, Type>::exec(const Base &event) const {
    const Type &derived = static_cast<const Type &>(event);
    (m_instance.*m_callbackMethod)(const_cast<Type &>(derived));
}

template <typename Type>
LambdaCallback<Type>::LambdaCallback(std::function<void(Type &)> callback)
    : m_callback(std::move(callback)) {
}

template <typename Type>
void LambdaCallback<Type>::exec(const Base &event) const {
    const Type &derived = static_cast<const Type &>(event);
    m_callback(const_cast<Type &>(derived));
}

} // namespace ecs::system::event
