#pragma once
#include <SFML/Graphics.hpp>

class Game;

namespace State {
    
class State {
protected:
    Game& m_game;
    bool m_wantExit = false;

public:
    
    State(Game& game) : m_game(game) {};
    virtual ~State() = default;

    virtual void update(const sf::Time deltaTime, bool fixed = false) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
    virtual void handleEvent(sf::Event e) = 0;

    virtual void pause() {}
    virtual void resume() {}

    void wantExit(){
        m_wantExit = true;
    }

    bool checkIfWnatToExit(){
        return m_wantExit;
    }

    std::string makePath(const int which) {
        return "../res/levels/official/test" + std::to_string(which) + ".json"; 
    }
};

} // namespace State