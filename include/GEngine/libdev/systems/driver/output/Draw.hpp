/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) System
** ════════════════════════════════════════════════════════════════════════════
**  File        : Draw.hpp
**  Create at   : 2024-10-15 05:01
**  Author      : AUTHOR
**  Description : DESCRIPTION // TODO popoche
** ═══════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include "module/raylib_safe.h"
#include <set>

#include "GEngine/libdev/components/Transforms.hpp"
#include "GEngine/libdev/components/driver/output/Drawable.hpp"
#include "GEngine/libdev/components/driver/output/Shape.hpp"
#include "GEngine/libdev/components/driver/output/Sprite.hpp"
#include "GEngine/libdev/components/driver/output/Text.hpp"

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/driver/output/FontManager.hpp"
#include "GEngine/libdev/systems/driver/output/TextureManager.hpp"

#include "GEngine/libdev/systems/events/Native.hpp"
#include "GEngine/libdev/systems/events/RenderLoop.hpp"
#include "GEngine/libdev/systems/events/driver/output/Draw.hpp"

namespace gengine::system::driver::output {
class Draw2D : public gengine::System<Draw2D, component::driver::output::Drawable> {
public:
    Draw2D(const Color &clear = WHITE);

    void init(void) override;

    void onRenderLoop(gengine::system::event::RenderLoop &e);

    void onBeginDraw(gengine::system::event::BeginDraw &e);
    void onEndDraw(gengine::system::event::EndDraw &e);

private:
    Color m_clear;
};

class DrawSprite : public gengine::System<DrawSprite, component::driver::output::Sprite, component::Transform2D,
                                          system::driver::output::TextureManager> {
public:
    void init(void) override;

    void onDraw(gengine::system::event::Draw &e);
};

class DrawText : public gengine::System<DrawText, component::driver::output::Text, component::Transform2D,
                                        system::driver::output::FontManager> {
public:
    void init(void) override;

    void onDraw(gengine::system::event::Draw &e);
};

class DrawRectangle
    : public gengine::System<DrawRectangle, component::driver::output::Rectangle, component::Transform2D> {
public:
    void init(void) override;

    void onDraw(gengine::system::event::Draw &e);
};

class DrawCircle : public gengine::System<DrawCircle, component::driver::output::Circle, component::Transform2D> {
public:
    void init(void) override;

    void onDraw(gengine::system::event::Draw &e);
};
} // namespace gengine::system::driver::output