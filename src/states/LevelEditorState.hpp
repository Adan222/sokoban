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
#include "level/LevelEditor.hpp"
#include "Game.hpp"
#include <nfd.h>


namespace State {


class LevelEditorState : public State {
    //LevelConfig must be first here 
    LevelConfig m_levelConfig;
    LevelEditor m_editor;
    std::filesystem::path m_jsonPath;

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