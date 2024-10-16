/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** DrawScore.cpp
*/

#include "systems/UpdateScoreText.hpp"

// #include <format>

namespace rtype::system {
void UpdateScoreText::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&UpdateScoreText::onGameLoop);
}

void UpdateScoreText::onGameLoop(gengine::system::event::GameLoop &e) {
    auto &scores = getComponents<component::Score>();
    auto &players = getComponents<gengine::interface::component::RemoteDriver>();

    int totalScore = 0;

    for (auto [entity, score, player] : gengine::Zip(scores, players))
        totalScore += score.score;

    auto &scoreTexts = getComponents<component::ScoreText>();
    auto &texts = getComponents<gengine::component::driver::output::Text>();

    for (auto [entity, scoreText, text] : gengine::Zip(scoreTexts, texts))
        std::strncpy(text.str.data(), (std::string("Score: ") + std::to_string(totalScore).c_str()).c_str(), 64);
    // text.str = "Score: " + std::to_string(totalScore);
}
} // namespace rtype::system
