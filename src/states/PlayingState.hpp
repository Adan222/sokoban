#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace State {

class PlayingState : public State {
    sf::CircleShape m_shape;        
public:
    PlayingState(Game& game);
    ~PlayingState();
    
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
};

}

