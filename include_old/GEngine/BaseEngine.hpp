/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** AEngine.hpp
*/

#pragma once

#include "ecs/system/Base.hpp" // includes ECS (avoid circular include)

#include <functional>
#include <memory>

namespace gengine {
class BaseEngine {
public:
    // TODO add constructor whit Interface Type template
    template <typename T, typename... Params> inline void registerSystem(Params &&...p);

    template <typename T> inline void registerComponent(void);

    void compute(void);

    void start(void);

private:
    ecs::ECS m_ecs;
};
} // namespace gengine

#include "BaseEngine.inl"
