#pragma once


#include <iostream>
#include <memory>
#include <chrono>

#include "State.hpp"
#include "Game.hpp"


namespace State {


class LevelEditorState : public State {
    
public:
    LevelEditorState(Game& game);
    ~LevelEditorState();

    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
    
    void pause() override;
    void resume() override;
};


}