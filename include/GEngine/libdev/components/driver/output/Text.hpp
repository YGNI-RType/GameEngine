/*
** ════════════════════════════════════════════════════════════════════════════
**                           GEngine (libdev) Component
** ════════════════════════════════════════════════════════════════════════════
**  File        : Text.hpp
**  Create at   : 2024-10-15 05:26
**  Auteur      : AUTHOR
**  Description : DESCRIPTION // TODO popoche
** ════════════════════════════════════════════════════════════════════════════
*/

#pragma once

#include <raylib.h>
#include <string>

#include "GEngine/libdev/Component.hpp"
#include "GEngine/libdev/components/driver/output/RaylibTypes.hpp"

namespace gengine::component::driver::output {
struct Text : public Component<Text> {
    std::string fontPath;
    std::string str;
    float fontSize;
    float spacing;
    Clr tint;

    Text(const std::string &fontPath, const std::string &str, const Clr &tint = BLACK, float spacing = 0)
        : fontPath(fontPath)
        , str(str)
        , fontSize(10)
        , spacing(spacing)
        , tint(tint) {
    }

    bool operator==(const Text &) const = default;
};
} // namespace gengine::component::driver::output
