#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "LevelConfig.hpp"
#include "map/Map.hpp"
#include "Game.hpp"

namespace State {


class LevelEditorState : public State {
    int m_atlasTileSize;
    std::filesystem::path m_atlasFilePath;
    sf::Texture m_tileAtlasTexture;
    
    std::vector<sf::Sprite> m_tilesRectList;

    LevelConfig m_levelConfig;
    Map m_m1;

    void tileSelectionBox();
    void setUpTileRectList();
    void initValuesFromJSON();
public:
    
    LevelEditorState(Game& game);
    ~LevelEditorState();

    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
    
    void pause() override;
    void resume() override;
};


} //namespace State