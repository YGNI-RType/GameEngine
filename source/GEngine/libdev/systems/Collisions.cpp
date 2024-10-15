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

bool checkSquareCollision(const component::HitBoxSquare2D &square1, const component::Transform2D &tr1,
                          const component::HitBoxSquare2D &square2, const component::Transform2D &tr2) {
    return !(tr1.pos.x > tr2.pos.x + square2.width * tr2.scale.x || tr1.pos.x + square1.width * tr1.scale.x < tr2.pos.x ||
             tr1.pos.y > tr2.pos.y + square2.height * tr2.scale.y || tr1.pos.y + square1.height * tr1.scale.y < tr2.pos.y);
}

bool checkCircleCollision(const component::HitBoxCircle2D &circle1, const component::Transform2D &tr1,
                          const component::HitBoxCircle2D &circle2, const component::Transform2D &tr2) {
    float dx = (tr1.pos.x + circle1.radius * tr1.scale.x) - (tr2.pos.x + circle2.radius * tr2.scale.x);
    float dy = (tr1.pos.y + circle1.radius * tr1.scale.x) - (tr2.pos.y + circle2.radius * tr2.scale.x);
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (circle1.radius * tr1.scale.x + circle2.radius * tr2.scale.x);
}

bool checkSquareCircleCollision(const component::HitBoxSquare2D &square, const component::Transform2D &trSquare,
                                const component::HitBoxCircle2D &circle, const component::Transform2D &trCircle) {
    float closestX = std::clamp(trCircle.pos.x + circle.radius * trCircle.scale.x, trSquare.pos.x,
                                trSquare.pos.x + square.width * trSquare.scale.x);
    float closestY = std::clamp(trCircle.pos.y + circle.radius * trCircle.scale.x, trSquare.pos.y,
                                trSquare.pos.y + square.height * trSquare.scale.y);
    float dx = (trCircle.pos.x + circle.radius * trCircle.scale.x) - closestX;
    float dy = (trCircle.pos.y + circle.radius * trCircle.scale.x) - closestY;
    return (dx * dx + dy * dy) < (circle.radius * trCircle.scale.x + circle.radius * trCircle.scale.x);
}

void Collision2D::onMainLoop(event::MainLoop &e [[maybe_unused]]) {
    auto &transforms = getComponents<component::Transform2D>();
    // auto &origins = getComponents<component::Origin2D>();
    auto &hitboxSquares = getComponents<component::HitBoxSquare2D>();
    auto &hitboxCircles = getComponents<component::HitBoxCircle2D>();

    for (auto [entity1, tr] : transforms) {
        for (auto [entity2, tr2] : transforms) {
            if (entity1 == entity2)
                continue;

            // if (origins.contains(entity1)) {
            //     tr.pos.x += origins.get(entity1).x;
            //     tr.pos.y += origins.get(entity1).y;
            // }

            // if (origins.contains(entity2)) {
            //     tr2.pos.x += origins.get(entity2).x;
            //     tr2.pos.y += origins.get(entity2).y;
            // }

            bool entity1HasSquare = hitboxSquares.contains(entity1);
            bool entity1HasCircle = hitboxCircles.contains(entity1);
            bool entity2HasSquare = hitboxSquares.contains(entity2);
            bool entity2HasCircle = hitboxCircles.contains(entity2);

            if (entity1HasSquare && entity2HasSquare) {
                const auto &square1 = hitboxSquares.get(entity1);
                const auto &square2 = hitboxSquares.get(entity2);
                if (checkSquareCollision(square1, tr, square2, tr2.pos))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasCircle && entity2HasCircle) {
                const auto &circle1 = hitboxCircles.get(entity1);
                const auto &circle2 = hitboxCircles.get(entity2);
                if (checkCircleCollision(circle1, tr, circle2, tr2.pos))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasSquare && entity2HasCircle) {
                const auto &square = hitboxSquares.get(entity1);
                const auto &circle = hitboxCircles.get(entity2);
                if (checkSquareCircleCollision(square, tr, circle, tr2))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasCircle && entity2HasSquare) {
                const auto &circle = hitboxCircles.get(entity1);
                const auto &square = hitboxSquares.get(entity2);
                if (checkSquareCircleCollision(square, tr2, circle, tr))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            }
        }
    }
}

void Collision3D::init(void) {
    subscribeToEvent<event::MainLoop>(&Collision3D::onMainLoop);
}

bool checkCubeCollision(const component::HitBoxSquare3D &cube1, const component::Transform3D &tr1,
                        const component::HitBoxSquare3D &cube2, const component::Transform3D &tr2) {
    return !(tr1.pos.x > tr2.pos.x + cube2.width || tr1.pos.x + cube1.width < tr2.pos.x ||
             tr1.pos.y > tr2.pos.y + cube2.height || tr1.pos.y + cube1.height < tr2.pos.y ||
             tr1.pos.z > tr2.pos.z + cube2.depth || tr1.pos.z + cube1.depth < tr2.pos.z);
}

bool checkSphereCollision(const component::HitBoxCircle3D &sphere1, const component::Transform3D &tr1,
                          const component::HitBoxCircle3D &sphere2, const component::Transform3D &tr2) {
    float dx = (tr1.pos.x + sphere1.radius) - (tr2.pos.x + sphere2.radius);
    float dy = (tr1.pos.y + sphere1.radius) - (tr2.pos.y + sphere2.radius);
    float dz = (tr1.pos.z + sphere1.radius) - (tr2.pos.z + sphere2.radius);
    float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    return distance < (sphere1.radius + sphere2.radius);
}

bool checkCubeSphereCollision(const component::HitBoxSquare3D &cube, const component::Transform3D &trCube,
                              const component::HitBoxCircle3D &sphere, const component::Transform3D &trSphere) {
    float closestX = std::clamp(trSphere.pos.x + sphere.radius, trCube.pos.x, trCube.pos.x + cube.width);
    float closestY = std::clamp(trSphere.pos.y + sphere.radius, trCube.pos.y, trCube.pos.y + cube.height);
    float closestZ = std::clamp(trSphere.pos.z + sphere.radius, trCube.pos.z, trCube.pos.z + cube.depth);
    float dx = (trSphere.pos.x + sphere.radius) - closestX;
    float dy = (trSphere.pos.y + sphere.radius) - closestY;
    float dz = (trSphere.pos.z + sphere.radius) - closestZ;
    return (dx * dx + dy * dy + dz * dz) < (sphere.radius * sphere.radius);
}

void Collision3D::onMainLoop(event::MainLoop &e [[maybe_unused]]) {
    auto &transforms = getComponents<component::Transform3D>();
    // auto &origins = getComponents<component::Origin3D>();
    auto &hitboxCubes = getComponents<component::HitBoxSquare3D>();
    auto &hitboxSpheres = getComponents<component::HitBoxCircle3D>();

    for (auto [entity1, tr1] : transforms) {
        for (auto [entity2, tr2] : transforms) {
            if (entity1 == entity2)
                continue;

            // if (origins.contains(entity1)) {
            //     tr1.pos.x += origins.get(entity1).x;
            //     tr1.pos.y += origins.get(entity1).y;
            // }

            // if (origins.contains(entity2)) {
            //     tr2.pos.x += origins.get(entity2).x;
            //     tr2.pos.y += origins.get(entity2).y;
            // }

            bool entity1HasCube = hitboxCubes.contains(entity1);
            bool entity1HasSphere = hitboxSpheres.contains(entity1);
            bool entity2HasCube = hitboxCubes.contains(entity2);
            bool entity2HasSphere = hitboxSpheres.contains(entity2);

            if (entity1HasCube && entity2HasCube) {
                const auto &cube1 = hitboxCubes.get(entity1);
                const auto &cube2 = hitboxCubes.get(entity2);
                if (checkCubeCollision(cube1, tr1.pos, cube2, tr2.pos))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasSphere && entity2HasSphere) {
                const auto &sphere1 = hitboxSpheres.get(entity1);
                const auto &sphere2 = hitboxSpheres.get(entity2);
                if (checkSphereCollision(sphere1, tr1.pos, sphere2, tr2.pos))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasCube && entity2HasSphere) {
                const auto &cube = hitboxCubes.get(entity1);
                const auto &sphere = hitboxSpheres.get(entity2);
                if (checkCubeSphereCollision(cube, tr1.pos, sphere, tr2.pos))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            } else if (entity1HasSphere && entity2HasCube) {
                const auto &sphere = hitboxSpheres.get(entity1);
                const auto &cube = hitboxCubes.get(entity2);
                if (checkCubeSphereCollision(cube, tr2.pos, sphere, tr1.pos))
                    publishEvent(gengine::system::event::Collsion(entity1, entity2));
            }
        }
    }
}
} // namespace gengine::system
