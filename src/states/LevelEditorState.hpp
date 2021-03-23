#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "level/LevelConfig.hpp"
#include "map/Map.hpp"
#include "map/Grid.hpp"
#include "Game.hpp"

namespace State {


class LevelEditorState : public State {
    int m_atlasTileSize;
    uint32_t m_tileAtlasColumns;
    std::filesystem::path m_atlasFilePath;
    sf::Vector2u m_tileAtlasFileTxtSize;
    sf::Texture m_tileAtlasTexture;
    sf::Sprite m_selectedTile;
    std::vector<sf::Sprite> m_tilesRectList;
    std::vector<sf::FloatRect> m_gridSquaresBounds;
    //LevelConfig must be first here 
    LevelConfig m_levelConfig;
    Map m_m1;
    Grid m_g1;

    void mainPanel();
    void tileSelectionBox();
    void setUpTileRectList();
    void tileSelected(const sf::Sprite& ts);
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