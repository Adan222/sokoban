#pragma once

#include <iostream>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "objects/Player.hpp"
#include "config.hpp"

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

}

