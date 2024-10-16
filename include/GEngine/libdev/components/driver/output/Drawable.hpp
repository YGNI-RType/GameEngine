/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Component
** ════════════════════════════════════════════════════════════════════════════
**  File        : Drawable.hpp
**  Create at   : 2024-10-15 05:25
**  Auteur      : AUTHOR
**  Description : DESCRIPTION // TODO popoche
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include <cstdlib>

#include "GEngine/libdev/Component.hpp"

namespace gengine::component::driver::output {
struct Drawable : public Component<Drawable> {
    std::size_t zIndex;
    Drawable(std::size_t zIndex)
        : zIndex(zIndex) {
    }

    bool operator==(const Drawable &) const = default;
};
} // namespace gengine::component::driver::output