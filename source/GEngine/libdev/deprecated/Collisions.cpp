/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Collision.cpp
*/
#include "GEngine/libdev/systems/Collisions.hpp"
#include <algorithm>
#include <cmath>

namespace gengine::system {

void Collision2D::init(void) {
    subscribeToEvent<event::MainLoop>(&Collision2D::onMainLoop);
}

bool checkSquareCollision(const component::HitBoxSquare2D &square1, const component::Position2D &pos1,
                          const component::HitBoxSquare2D &square2, const component::Position2D &pos2) {
    return !(pos1.x > pos2.x + square2.width || pos1.x + square1.width < pos2.x || pos1.y > pos2.y + square2.height ||
             pos1.y + square1.height < pos2.y);
}

bool checkCircleCollision(const component::HitBoxCircle2D &circle1, const component::Position2D &pos1,
                          const component::HitBoxCircle2D &circle2, const component::Position2D &pos2) {
    float dx = (pos1.x + circle1.radius) - (pos2.x + circle2.radius);
    float dy = (pos1.y + circle1.radius) - (pos2.y + circle2.radius);
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (circle1.radius + circle2.radius);
}

bool checkSquareCircleCollision(const component::HitBoxSquare2D &square, const component::Position2D &posSquare,
                                const component::HitBoxCircle2D &circle, const component::Position2D &posCircle) {
    float closestX = std::clamp(posCircle.x + circle.radius, posSquare.x, posSquare.x + square.width);
    float closestY = std::clamp(posCircle.y + circle.radius, posSquare.y, posSquare.y + square.height);
    float dx = (posCircle.x + circle.radius) - closestX;
    float dy = (posCircle.y + circle.radius) - closestY;
    return (dx * dx + dy * dy) < (circle.radius * circle.radius);
}

void Collision2D::onMainLoop(event::MainLoop &e [[maybe_unused]]) {
    auto &positions = getComponents<component::Position2D>();
    auto &origins = getComponents<component::Origin2D>();
    auto &hitboxSquares = getComponents<component::HitBoxSquare2D>();
    auto &hitboxCircles = getComponents<component::HitBoxCircle2D>();

    for (auto [entity1, pos1] : positions) {
        for (auto [entity2, pos2] : positions) {
            if (entity1 == entity2)
                continue;

            if (origins.contains(entity1)) {
                pos1.x += origins.get(entity1).x;
                pos1.y += origins.get(entity1).y;
            }

            if (origins.contains(entity2)) {
                pos2.x += origins.get(entity2).x;
                pos2.y += origins.get(entity2).y;
            }

            bool entity1HasSquare = hitboxSquares.contains(entity1);
            bool entity1HasCircle = hitboxCircles.contains(entity1);
            bool entity2HasSquare = hitboxSquares.contains(entity2);
            bool entity2HasCircle = hitboxCircles.contains(entity2);

            if (entity1HasSquare && entity2HasSquare) {
                const auto &square1 = hitboxSquares.get(entity1);
                const auto &square2 = hitboxSquares.get(entity2);
                if (checkSquareCollision(square1, pos1, square2, pos2))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasCircle && entity2HasCircle) {
                const auto &circle1 = hitboxCircles.get(entity1);
                const auto &circle2 = hitboxCircles.get(entity2);
                if (checkCircleCollision(circle1, pos1, circle2, pos2))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasSquare && entity2HasCircle) {
                const auto &square = hitboxSquares.get(entity1);
                const auto &circle = hitboxCircles.get(entity2);
                if (checkSquareCircleCollision(square, pos1, circle, pos2))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasCircle && entity2HasSquare) {
                const auto &circle = hitboxCircles.get(entity1);
                const auto &square = hitboxSquares.get(entity2);
                if (checkSquareCircleCollision(square, pos2, circle, pos1))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            }
        }
    }
}

void Collision3D::init(void) {
    subscribeToEvent<event::MainLoop>(&Collision3D::onMainLoop);
}

bool checkCubeCollision(const component::HitBoxSquare3D &cube1, const component::Position3D &pos1,
                        const component::HitBoxSquare3D &cube2, const component::Position3D &pos2) {
    return !(pos1.x > pos2.x + cube2.width || pos1.x + cube1.width < pos2.x || pos1.y > pos2.y + cube2.height ||
             pos1.y + cube1.height < pos2.y || pos1.z > pos2.z + cube2.depth || pos1.z + cube1.depth < pos2.z);
}

bool checkSphereCollision(const component::HitBoxCircle3D &sphere1, const component::Position3D &pos1,
                          const component::HitBoxCircle3D &sphere2, const component::Position3D &pos2) {
    float dx = (pos1.x + sphere1.radius) - (pos2.x + sphere2.radius);
    float dy = (pos1.y + sphere1.radius) - (pos2.y + sphere2.radius);
    float dz = (pos1.z + sphere1.radius) - (pos2.z + sphere2.radius);
    float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    return distance < (sphere1.radius + sphere2.radius);
}

bool checkCubeSphereCollision(const component::HitBoxSquare3D &cube, const component::Position3D &posCube,
                              const component::HitBoxCircle3D &sphere, const component::Position3D &posSphere) {
    float closestX = std::clamp(posSphere.x + sphere.radius, posCube.x, posCube.x + cube.width);
    float closestY = std::clamp(posSphere.y + sphere.radius, posCube.y, posCube.y + cube.height);
    float closestZ = std::clamp(posSphere.z + sphere.radius, posCube.z, posCube.z + cube.depth);
    float dx = (posSphere.x + sphere.radius) - closestX;
    float dy = (posSphere.y + sphere.radius) - closestY;
    float dz = (posSphere.z + sphere.radius) - closestZ;
    return (dx * dx + dy * dy + dz * dz) < (sphere.radius * sphere.radius);
}

void Collision3D::onMainLoop(event::MainLoop &e [[maybe_unused]]) {
    auto &positions = getComponents<component::Position3D>();
    auto &origins = getComponents<component::Origin3D>();
    auto &hitboxCubes = getComponents<component::HitBoxSquare3D>();
    auto &hitboxSpheres = getComponents<component::HitBoxCircle3D>();

    for (auto [entity1, pos1] : positions) {
        for (auto [entity2, pos2] : positions) {
            if (entity1 == entity2)
                continue;

            if (origins.contains(entity1)) {
                pos1.x += origins.get(entity1).x;
                pos1.y += origins.get(entity1).y;
            }

            if (origins.contains(entity2)) {
                pos2.x += origins.get(entity2).x;
                pos2.y += origins.get(entity2).y;
            }

            bool entity1HasCube = hitboxCubes.contains(entity1);
            bool entity1HasSphere = hitboxSpheres.contains(entity1);
            bool entity2HasCube = hitboxCubes.contains(entity2);
            bool entity2HasSphere = hitboxSpheres.contains(entity2);

            if (entity1HasCube && entity2HasCube) {
                const auto &cube1 = hitboxCubes.get(entity1);
                const auto &cube2 = hitboxCubes.get(entity2);
                if (checkCubeCollision(cube1, pos1, cube2, pos2))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasSphere && entity2HasSphere) {
                const auto &sphere1 = hitboxSpheres.get(entity1);
                const auto &sphere2 = hitboxSpheres.get(entity2);
                if (checkSphereCollision(sphere1, pos1, sphere2, pos2))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasCube && entity2HasSphere) {
                const auto &cube = hitboxCubes.get(entity1);
                const auto &sphere = hitboxSpheres.get(entity2);
                if (checkCubeSphereCollision(cube, pos1, sphere, pos2))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasSphere && entity2HasCube) {
                const auto &sphere = hitboxSpheres.get(entity1);
                const auto &cube = hitboxCubes.get(entity2);
                if (checkCubeSphereCollision(cube, pos2, sphere, pos1))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            }
        }
    }
}
} // namespace gengine::system
