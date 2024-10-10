/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** Snapshot.hpp
*/

#pragma once

#include <cstdint>

namespace gengine::interface::network::system {
struct NetworkComponent {
    uint64_t entity;
    uint16_t typeId;
    uint16_t size;

    NetworkComponent(uint64_t entity = 0, uint16_t typeId = 0, uint16_t size = 0)
        : entity(entity)
        , typeId(typeId)
        , size(size) {
    }
};
} // namespace gengine::interface::network::system