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

    /**
     * Exit state will be aat the end of game loop
     * couse when we exit before we can have "Segmentation fault".
     * So now state signal that he want to exit and exit at the end
     * of main loop
     */
    void popState();
public:
    Game();
    ~Game();

    void pushState(std::unique_ptr<State::State> state);
    void run();
    void exit();

public:    
    sf::Vector2u getWindowSize() const;
    uint32_t getWindowWidth() const;
    uint32_t getWindowHeight() const;
    sf::Vector2i getMousePos() const;
    sf::RenderWindow &getWindow() ;
};