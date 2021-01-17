#pragma once

#include <iostream>
#include <memory>
#include <chrono>

#include "State.hpp"
#include "Game.hpp"
#include "PlayingState.hpp"

namespace State {


class MainMenuState : public State{
    sf::CircleShape m_shape;

    std::chrono::time_point<std::chrono::steady_clock> m_pauseTime;

public:
    MainMenuState(Game& game);
    ~MainMenuState();

    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
    
    void pause() override;
    void resume() override;
};


}