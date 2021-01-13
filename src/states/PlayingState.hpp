#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
namespace State {

class PlayingState : public State {

    sf::CircleShape m_shape;
    
public:
    PlayingState();
    ~PlayingState();
    
    bool wantTerminateSelf() override;
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
};

}

