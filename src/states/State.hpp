#pragma once
#include <SFML/Graphics.hpp>

class Game;

namespace State {
    
class State {
protected:
    Game& m_Game;
public:
    
    State(Game& game) : m_Game(game) {};
    virtual ~State() = default;

    virtual void handleEvent(sf::Event e) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;    
};

}