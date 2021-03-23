#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"

#include "level/LevelConfig.hpp"
#include <SFML/Graphics.hpp>
#include "map/Tile.hpp"

#include <vector>
class Map;

class EditorGui : public sf::Drawable, public sf::Transformable {
    LevelConfig& m_levelConfig;
    
    
    std::vector<Tile> m_tilesRectList;
    Tile m_selectedTile;
    
    uint32_t m_tilesRectColumns;
    uint32_t m_tilesRectRows;
    void tileList(Map& m1);

public:
    void setUpTileList(Map &m1);
    void header();
    void mainPanel(Map &m1);
    void updateSelectedTilePosition();
    void placeTile(Map &m1);

    //inherited from Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    EditorGui(LevelConfig& levelConfig);
    ~EditorGui();
};