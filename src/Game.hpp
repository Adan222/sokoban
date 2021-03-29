#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <vector>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"

#include "gui/FpsCounter.hpp"
#include "states/State.hpp"
#include "states/PlayingState.hpp"
#include "states/MainMenuState.hpp"
#include "states/LevelEditorState.hpp"



class Game {
private:
    sf::RenderWindow m_window;
    FpsCounter m_fps;
    std::vector<std::unique_ptr<State::State>> m_states;

    State::State& getCurrentState() const;
    void handleEvent();
public:
    Game();
    ~Game();

    void pushState(std::unique_ptr<State::State> state);
    void popState();
    void run();
    void exit();
    sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
public:    
    sf::Vector2u getWindowSize() const;
    uint32_t getWindowWidth() const;
    uint32_t getWindowHeight() const;
    sf::Vector2i getMousePos() const;
    sf::RenderWindow &getWindow() ;
};