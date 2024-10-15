/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Draw.cpp
*/

#include "GEngine/libdev/systems/driver/output/Draw.hpp"
#include <iostream>
#include <rlgl.h>

namespace gengine::system::driver::output {
struct zIndexComparator {
    bool operator()(const std::pair<Entity, int> &lhs, const std::pair<Entity, int> &rhs) const {
        return lhs.second < rhs.second;
    }
};

Draw2D::Draw2D(const Color &clear)
    : m_clear(clear) {
}

void Draw2D::init(void) {
    subscribeToEvent<gengine::system::event::RenderLoop>(&Draw2D::onRenderLoop);
    subscribeToEvent<gengine::system::event::BeginDraw>(&Draw2D::onBeginDraw);
    subscribeToEvent<gengine::system::event::EndDraw>(&Draw2D::onEndDraw);
}

void Draw2D::onRenderLoop(gengine::system::event::RenderLoop &e) {
    publishEvent(gengine::system::event::BeginDraw(m_clear));
    auto &drawables = getComponents<component::driver::output::Drawable>();

    std::multiset<std::pair<Entity, int>, zIndexComparator> toDraw;
    for (auto &[entity, drawable] : drawables)
        toDraw.emplace(entity, drawable.zIndex);

    for (auto &[entity, zIndex] : toDraw)
        publishEvent(gengine::system::event::Draw(entity));
    publishEvent(gengine::system::event::EndDraw());
}

void Draw2D::onBeginDraw(gengine::system::event::BeginDraw &e) {
    // BeginDrawing();
    ClearBackground(e.clear);
}
void Draw2D::onEndDraw(gengine::system::event::EndDraw &e) {
    rlDrawRenderBatchActive();
    SwapScreenBuffer();
}

void DrawSprite::init(void) {
    subscribeToEvent<gengine::system::event::Draw>(&DrawSprite::onDraw);
}

void DrawSprite::onDraw(gengine::system::event::Draw &e) {
    auto &sprites = getComponents<component::driver::output::Sprite>();
    auto &transforms = getComponents<gengine::component::Transform2D>();

    auto &txtMan = getSystem<TextureManager>();
    if (sprites.contains(e.entity) && transforms.contains(e.entity)) {
        auto &[path, src, tint] = sprites.get(e.entity);
        auto &[pos, scale, rotation] = transforms.get(e.entity);
        Rectangle r = {pos.x, pos.y, src.width * scale.x, src.height * scale.y};
        DrawTexturePro(txtMan.get(path), src, r, {0, 0}, rotation, tint); // TODO origin
    }
}

void DrawText::init(void) {
    subscribeToEvent<gengine::system::event::Draw>(&DrawText::onDraw);
}

void DrawText::onDraw(gengine::system::event::Draw &e) {
    auto &texts = getComponents<component::driver::output::Text>();
    auto &transforms = getComponents<gengine::component::Transform2D>();

    auto &fontMan = getSystem<FontManager>();
    if (texts.contains(e.entity) && transforms.contains(e.entity)) {
        auto &[path, str, fontSize, spacing, tint] = texts.get(e.entity);
        auto &[pos, scale, rotation] = transforms.get(e.entity);
        DrawTextPro(fontMan.get(path), str.c_str(), Vector2{pos.x, pos.y}, {0, 0}, rotation, fontSize * scale.y,
                    spacing, tint); // TODO origin
    }
}

void DrawRectangle::init(void) {
    subscribeToEvent<gengine::system::event::Draw>(&DrawRectangle::onDraw);
}

void DrawRectangle::onDraw(gengine::system::event::Draw &e) {
    auto &rectangles = getComponents<component::driver::output::Rectangle>();
    auto &transforms = getComponents<gengine::component::Transform2D>();

    if (rectangles.contains(e.entity) && transforms.contains(e.entity)) {
        auto &[width, height, color] = rectangles.get(e.entity);
        auto &[pos, scale, rotation] = transforms.get(e.entity);
        Rectangle r = {pos.x, pos.y, width * scale.x, height * scale.y};
        DrawRectanglePro(r, {0, 0}, rotation, color); // TODO origin
    }
}

void DrawCircle::init(void) {
    subscribeToEvent<gengine::system::event::Draw>(&DrawCircle::onDraw);
}

void DrawCircle::onDraw(gengine::system::event::Draw &e) {
    auto &circles = getComponents<component::driver::output::Circle>();
    auto &transforms = getComponents<gengine::component::Transform2D>();

    if (circles.contains(e.entity) && transforms.contains(e.entity)) {
        auto &[r, color] = circles.get(e.entity);
        auto &[pos, scale, rotation] = transforms.get(e.entity);
        ::DrawCircle(pos.x, pos.y, r * scale.x, color);
    }
}
} // namespace gengine::system::driver::output
