#pragma once

#include <iostream>
#include <chrono>
#include <exception>

#include "State.hpp"
#include "Game.hpp"
#include "level/Level.hpp"

#define LEVEL_PATH "../res/levels/"

namespace State {

class PlayingState : public State {
    Level *m_level;
    int m_whichLvl;
    
public:
    PlayingState(Game& game);
    ~PlayingState();
    
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;

    void update(const float deltaTime) override;
    
    void setWhichLvl(const int which);
};

}

