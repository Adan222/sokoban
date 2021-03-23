#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "level/LevelConfig.hpp"
#include "gui/EditorGui.hpp"
#include "map/Map.hpp"
#include "Game.hpp"

namespace State {


class LevelEditorState : public State {
    //LevelConfig must be first here 
    LevelConfig m_levelConfig;
    EditorGui m_editorGui;
    Map m_m1;

public:
    LevelEditorState(Game& game);
    ~LevelEditorState();

    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
    void update(float deltaTime) override;

    void pause() override;
    void resume() override;
};


} //namespace State