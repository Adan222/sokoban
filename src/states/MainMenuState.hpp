#pragma once

#include <iostream>
#include <memory>
#include <chrono>

#include "State.hpp"
#include "../Game.hpp"
#include "PlayingState.hpp"

namespace State {


class MainMenuState : public State{
    sf::CircleShape m_shape;

public:
    MainMenuState(Game& game);
    ~MainMenuState();

    void update(float deltaTime) override;
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
};


}