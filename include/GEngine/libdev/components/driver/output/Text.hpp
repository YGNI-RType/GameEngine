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

#include "module/raylib_safe.h"
#include <array>
#include <cstring>
#include <string>

#include "GEngine/libdev/Component.hpp"
#include "GEngine/libdev/components/driver/output/RaylibTypes.hpp"

namespace gengine::component::driver::output {
struct Text : public Component<Text> {
    std::array<char, 64> fontPath;
    std::array<char, 64> str;
    float fontSize;
    float spacing;
    Clr tint;

    Text(const std::string &fontPath, const std::string &str, const Clr &tint = BLACK, float spacing = 0)
        : fontSize(10)
        , spacing(spacing)
        , tint(tint) {

        size_t sz = std::min(this->fontPath.size() - 1, fontPath.size());
        std::strncpy(this->fontPath.data(), fontPath.c_str(), sz);
        this->fontPath[sz] = '\0';
        std::strncpy(this->str.data(), str.c_str(), std::min(this->str.size() - 1, str.size()));
        this->str[sz] = '\0';
    }

    bool operator==(const Text &other) const {
        return std::strcmp(this->fontPath.data(), other.fontPath.data()) == 0 &&
               std::strcmp(this->str.data(), other.str.data()) == 0 && this->fontSize == other.fontSize &&
               this->spacing == other.spacing && this->tint == other.tint;
    }
};
} // namespace gengine::component::driver::output
