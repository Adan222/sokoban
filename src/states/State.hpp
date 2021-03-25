#pragma once
#include <SFML/Graphics.hpp>

class Game;

namespace State {
    
class State {
protected:
    Game& m_game;
public:
    
    State(Game& game) : m_game(game) {};
    virtual ~State() = default;

    virtual void update(const float deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
    virtual void handleEvent(sf::Event e) = 0;

    //pauzuje/wznawia stejta
    //pryda sie jak bedziemy robic menu pod eskejpa
    //np czas zastopuje
    //resume jest wywolywany w popState
    //a pause przy pusznieciu
    virtual void pause() {};
    virtual void resume() {};

};

}