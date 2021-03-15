#pragma once
#include <cstddef>
#include <vector>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "config.hpp"
#include "fpsCounter.hpp"
#include "states/State.hpp"
#include "states/PlayingState.hpp"
#include "states/MainMenuState.hpp"

class Game {
private:
    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<State::State>> m_states;

    State::State& getCurrentState() const;
    void handleEvent();

    fpsCounter m_fps;
    
public:
    Game();
    ~Game();

    
    //pushState teraz pauzuje poprzedniego stejta
    //pauzuje bo nie usuwa xd tzn wiemy ze bedzie jescze istniec 
    //np jak menu chcemy wlaczyc 

    //popState wznawia stajeta chyba ze jest ostatni 

    void pushState(std::unique_ptr<State::State> state);
    void popState();
    void run();

    sf::Vector2u getWindowSize() const;
    int getWindowWidth() const;
    int getWindowHeight() const;
};