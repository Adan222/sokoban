#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"

class PlayingState : public State {
    sf::CircleShape m_shape;
    
public:
    PlayingState();
    ~PlayingState();
    
    void eventHandler() override;
    void draw(sf::RenderTarget& renderer) override;
};