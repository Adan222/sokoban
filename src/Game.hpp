#pragma once
#include <vector>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "SFML/System/Vector2.hpp"

#include "states/State.hpp"
#include "states/PlayingState.hpp"

class Game {
private:
    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<State::State>> m_states;
    sf::Vector2u m_window_size;

    State::State& getCurrentState() const;
    void handleEvent();
public:
    Game();
    ~Game();

    void pushState(std::unique_ptr<State::State> state);
    void popState();
    void run();
};