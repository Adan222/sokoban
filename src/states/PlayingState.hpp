#pragma once

#include <iostream>
#include <chrono>
#include <exception>

#include "State.hpp"
#include "Game.hpp"
#include "Level.hpp"

namespace State {

class PlayingState : public State {
    Level m_level;
    
public:
    PlayingState(Game& game);
    ~PlayingState();
    
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;

    void update(const float deltaTime) override;
};

} //namespace State

