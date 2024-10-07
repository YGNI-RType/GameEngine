/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Interface.hpp
*/

#pragma once

namespace gengine::interface {
class Base {
public:
    virtual ~Base() = default;
    virtual void run(void) = 0;
};
} // namespace gengine::interface
