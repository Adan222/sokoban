#pragma once
#include <cstddef>
#include <vector>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "config.hpp"
#include "fpsCounter.hpp"
#include "states/State.hpp"
#include "states/PlayingState.hpp"
#include "states/MainMenuState.hpp"
#include "states/LevelEditorState.hpp"

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


    void pushState(std::unique_ptr<State::State> state);
    void popState();
    void run();

    sf::Vector2u getWindowSize() const;
    int getWindowWidth() const;
    int getWindowHeight() const;
};