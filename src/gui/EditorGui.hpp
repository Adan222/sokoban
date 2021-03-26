#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"

#include "level/LevelConfig.hpp"
#include <SFML/Graphics.hpp>
#include "map/Tile.hpp"

#include <vector>

#include <nfd.h>
class Map;

class EditorGui : public sf::Drawable, public sf::Transformable {
    LevelConfig m_levelConfig;
    
    Tile* m_selectedTile;
    Tile m_liftedTile;
    
    std::vector<Tile> m_tilesRectList;
    bool m_initialPopupShowed;
    std::filesystem::path m_jsonPath;
   
    void fileDialog();
    void tileList(Map& m1);
    void tileOptions();
    void mapSettings();

    void initialPrompt();
public:
    void setUpTileList(Map &m1);
    void header();
    void mainPanel(Map &m1);

    void updateSelectedTilePosition();
    void placeTile(Map &m1);
    void selectTile(Map &m1, sf::Vector2f mousePosition);

    void initialPopupShowed(bool showed);
    std::filesystem::path& getNewConfigPath();
    //inherited from Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    EditorGui(LevelConfig& levelConfig);
    ~EditorGui();
};