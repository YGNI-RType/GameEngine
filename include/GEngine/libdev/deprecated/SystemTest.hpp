/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** SystemTest.hpp
*/

#pragma once

#include <functional>
#include <queue>

#include "Sprite.hpp"

namespace ecs {
class System {
public:
    virtual void update(float dt) = 0;
    virtual ~System() = default;
};

class MovementSystem : public System {
public:
    MovementSystem(Core &core)
        : transforms(core.getComponents<Transform>())
        , velocities(core.getComponents<Motion>()) {
    }

    void update(float dt) override {
        for (auto &[entity, transform] : transforms) {
            if (velocities.contains(entity)) {
                auto &velocity = velocities.get(entity);
                transform.x += velocity.vx * dt;
                transform.y += velocity.vy * dt;
                // // std::cout << "Entity " << entity << " moved to (" <<
                // transform.x << ", " << transform.y << ")\n";
            }
        }
    }

private:
    SparseArray<Transform> &transforms;
    SparseArray<Motion> &velocities;
};

class DrawSystem : public System {
public:
    DrawSystem(Core &core)
        : sprites(core.getComponents<Sprite>())
        , transforms(core.getComponents<Transform>())
        , wd(sf::VideoMode(1000, 800), "title") {
    }

    void update(float dt) override {
        m_time -= dt;
        if (m_time > 0.01f)
            return;
        wd.clear();
        for (auto &[entity, sprite] : sprites) {
            if (transforms.contains(entity)) {
                auto &tr = transforms.get(entity);
                sprite.sp.setPosition({tr.x, tr.y});
                sprite.sp.setFillColor(sprite.col);
                wd.draw(sprite.sp);
            }
        }
        wd.display();
    }

private:
    float m_time = 0;
    sf::RenderWindow wd;
    SparseArray<Sprite> &sprites;
    SparseArray<Transform> &transforms;
};

class KillerSystem : public System {
public:
    KillerSystem(Core &core)
        : transforms(core.getComponents<Transform>())
        , m_core(core) {
    }

    void update(float dt) override {
        std::queue<Entity> toRemove;
        for (auto &[entity, transform] : transforms) {

            if (transform.y > 600) {
                toRemove.push(entity);
                // // std::cout << "killing " << entity << std::endl;

                // // std::cout << "size " << transforms.size() << std::endl;
                // for (auto& [entity, transform] : transforms)
                //     // std::cout << "[" << entity << "]";
                // // std::cout << std::endl;
            }
        }
        while (!toRemove.empty()) {
            m_core.killEntity(toRemove.front());
            toRemove.pop();
        }
    }

private:
    SparseArray<Transform> &transforms;
    Core &m_core;
};
} // namespace ecs