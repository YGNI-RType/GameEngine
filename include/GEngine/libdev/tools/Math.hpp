/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Math.hpp
*/

#pragma once

namespace gengine {
struct Vect2 {
    float x;
    float y;

    bool operator==(const Vect2 &) const = default;
}; // 2D Vector of GEngine

struct Vect3 {
    float x;
    float y;
    float z;

    bool operator==(const Vect3 &) const = default;
}; // 3D Vector of GEngine

struct VectInt2 {
    int x;
    int y;

    bool operator==(const VectInt2 &) const = default;
}; // 2D Vector of GEngine (int)

struct VectInt3 {
    int x;
    int y;
    int z;

    bool operator==(const VectInt3 &) const = default;
}; // 3D Vector of GEngine (int)
} // namespace gengine