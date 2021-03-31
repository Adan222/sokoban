#pragma once

#include <SFML/System/Time.hpp>
#include <iostream>
#include <exception>
#include <memory>

#include "State.hpp"
#include "Game.hpp"
#include "level/Level.hpp"
#include "PlayerConfig.hpp"

#define LEVEL_PATH "../res/levels/"

namespace State {

class PlayingState : public State {
    PlayerConfig m_playerConfig;
    Level m_level;
    
    int m_whichLvl;
    
public:
    PlayingState(Game& game);
    PlayingState(Game& game, const std::string playerName);
    
    ~PlayingState();
    
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;

    void update(const sf::Time deltaTime, bool fixed = false) override;

    void setWhichLvl(const int which);
};

}

