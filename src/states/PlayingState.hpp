#pragma once

#include <iostream>
#include <chrono>

#include "State.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "objects/Player.hpp"

namespace State {

class PlayingState : public State {
    //Level m_level;
    Objects::Player m_player;
    
public:
    PlayingState(Game& game);
    ~PlayingState();
    
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;

    void pause() override;
    void resume() override;
};

}

