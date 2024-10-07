/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Draw.cpp
*/

#include "GEngine/libdev/systems/driver/output/Draw.hpp"
#include <iostream>

namespace gengine::system::driver::output {
void Draw2D::init(void) { subscribeToEvent<gengine::system::event::Draw>(&Draw2D::onDraw); }

void Draw2D::onDraw(gengine::system::event::Draw &e) {
    auto &rectangles = getComponent<component::driver::output::Rectangle>();
    auto &circles = getComponent<component::driver::output::Circle>();
    auto &sprites = getComponent<component::driver::output::Sprite>();
    auto &transforms = getComponent<gengine::component::Transform2D>();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (auto &[entity, rect] : rectangles) {
        if (transforms.contains(entity)) {
            auto &[pos, scale, rotation] = transforms.get(entity);
            Rectangle r = {pos.x, pos.y, rect.width * scale.x, rect.height * scale.y};
            DrawRectanglePro(r, {0, 0}, rotation, rect.color); // TODO origin
            // DrawRectangle(pos.x, pos.y, rect.width * scale.x, rect.height * scale.y, rect.color);
        }
    }
    for (auto &[entity, circ] : circles) {
        if (transforms.contains(entity)) {
            auto &[pos, scale, rotation] = transforms.get(entity);
            DrawCircle(pos.x, pos.y, circ.r * scale.x, circ.color);
        }
    }
    for (auto &[entity, sprite] : sprites) {
        if (transforms.contains(entity)) {
            auto &[pos, scale, rotation] = transforms.get(entity);
            Rectangle r = {pos.x, pos.y, sprite.src.width * scale.x, sprite.src.height * scale.y};
            DrawTexturePro(sprite.texture, sprite.src, r, {r.width / 2, r.height / 2}, rotation, sprite.tint);
        }
    }
    EndDrawing();
}
} // namespace gengine::system::driver::output
