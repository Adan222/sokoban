#pragma once

#include <iostream>
#include <chrono>

#include "State.hpp"
#include "Game.hpp"
#include "Level.hpp"

namespace State {

class PlayingState : public State {
    sf::CircleShape m_shape;
    std::chrono::time_point<std::chrono::steady_clock> m_pauseTime;
    Level m_level;
public:
    PlayingState(Game& game);
    ~PlayingState();
    
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;

    void pause() override;
    void resume() override;
};

}

