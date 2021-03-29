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
private:
    std::reference_wrapper<LevelConfig> m_levelConfig;
    
    
    Tile* m_selectedTile;
    Tile m_liftedTile;
    
    std::vector<Tile> m_tilesRectList;
    bool m_initialPopupShowed;
    bool m_reload;


    //json files
    std::filesystem::path m_openPath; 
    std::filesystem::path m_savePath;

private:
    void openFileDialog();
    void saveFileDialog(Map& m1);

    void tileList(Map& m1);
    void tileOptions();
    void mapSettings(Map& m1);
    void errorFileLoading();
    void initialPrompt();

public:
    EditorGui(LevelConfig& levelConfig, bool initialPopupShowed);
    ~EditorGui();

    void setUpTileList(Map& m1);
    void mainPanel(Map& m1);
    
    void placeTile(Map& m1);
    void selectTile(Map& m1, sf::Vector2f mousePosition);
    void updateSelectedTilePosition();

    std::filesystem::path& getOpenPath();
    bool wantsReload() const;


    //inherited from Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};