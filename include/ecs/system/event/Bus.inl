/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Bus.inl
*/

#pragma once

namespace ecs::system::event {

template <typename Type>
void Bus::publish(const Type &event) {
    m_toExecute.push([this, event](void) -> void {
        auto it = m_callbacks.find(typeid(Type));

        if (it == m_callbacks.end())
            return;
        for (const auto &callback : it->second)
            callback->exec(event);
    });
}

template <typename T, typename Type>
void Bus::subscribe(T &instance, void (T::*callbackMethod)(Type &)) { // never use
    auto callback = std::make_unique<MethodCallback<T, Type>>(instance, callbackMethod);
    m_callbacks[typeid(Type)].emplace_back(std::move(callback));
}

template <typename Type>
void Bus::subscribe(std::function<void(Type &)> callback) {
    auto lambdaCallback = std::make_unique<LambdaCallback<Type>>(callback);
    m_callbacks[typeid(Type)].emplace_back(std::move(lambdaCallback));
}

} // namespace ecs::system::event
