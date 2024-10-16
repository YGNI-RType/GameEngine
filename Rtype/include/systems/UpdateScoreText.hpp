/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** UpdateScoreText.hpp
*/

#pragma once

#include "GEngine/interface/components/RemoteDriver.hpp"
#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/components/driver/output/Text.hpp"
#include "GEngine/libdev/systems/events/GameLoop.hpp"
#include "components/Score.hpp"
#include "components/ScoreText.hpp"

namespace rtype::system {
class UpdateScoreText
    : public gengine::System<UpdateScoreText, component::Score, component::ScoreText,
                             gengine::component::driver::output::Text, gengine::interface::component::RemoteDriver> {
public:
    void init(void) override;
    void onGameLoop(gengine::system::event::GameLoop &);
};
} // namespace rtype::system
