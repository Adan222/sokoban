#pragma once

#include <iostream>
#include <chrono>
#include <exception>


#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "entities/Player.hpp"



namespace State {

class PlayingState : public State {
    Level m_level;
    Player m_player;
    
public:
    PlayingState(Game& game);
    ~PlayingState();
    
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;

    void update(float deltaTime) override;

    void pause() override;
    void resume() override;
};

} //namespace State

