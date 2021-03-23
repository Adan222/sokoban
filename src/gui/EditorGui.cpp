#include "EditorGui.hpp"
#include <SFML/Graphics.hpp>
#include "map/Map.hpp"


EditorGui::EditorGui(LevelConfig& levelConfig) :  m_levelConfig(levelConfig), m_selectedTile(m_levelConfig.getTileSize()) {

}

EditorGui::~EditorGui() {
}


void EditorGui::setUpTileList(Map &m1) {
    const uint32_t tileSize = m_levelConfig.getTileSize();

    sf::Texture& tileAtlasTexture = m1.getTileAtlasTexture();
    sf::Vector2u tileAtlasTextureSize = tileAtlasTexture.getSize();
    const uint32_t tileAtlasColumns = m1.getTileAtlasColumns();

    const uint32_t numberOfTiles = (tileAtlasTextureSize.x  + 1)/ tileSize * (tileAtlasTextureSize.y  + 1) / tileSize;
    //to do number of tile in map function


    uint32_t row = 0, column = 0, actualTileTextureID = 0;
    float scale = 28.0f / static_cast<float>(tileSize);

    m_tilesRectList.clear();
    m_tilesRectList.resize(numberOfTiles, Tile(tileSize));

    for(auto &t : m_tilesRectList) {
        if(column %  tileAtlasColumns  == 0) {
            column = 0;
            ++row;
        }
        t.setTextureCoords(column, row, actualTileTextureID);
        t.setScale(scale, scale);
        ++actualTileTextureID;
        ++column;
    }

    m_tilesRectRows = row;
    m_tilesRectColumns = column;
}

void EditorGui::header() {
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    if(ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Opcje")) {
            if(ImGui::MenuItem("New")) {
                //Do something
            }
            ImGui::EndMenu();
        }
    ImGui::EndMainMenuBar();
    }
    ImGui::PopStyleVar();
}

void EditorGui::mainPanel(Map& m1) {
    ImGui::Begin("Lista kafelków", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Plik")) {
            if (ImGui::MenuItem("Otwórz inny plik z kafelkami", "Ctrl+O")) { /* Do stuff */ }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    tileList(m1);
    ImGui::End();
}


void EditorGui::tileList(Map& m1) {
    std::filesystem::path tileAtlasFilePath = m_levelConfig.getTileAtlasPath();
    uint32_t tileAtlasColumns = m1.getTileAtlasColumns();
    int tileSize = m_levelConfig.getTileSize();
    
    uint16_t im_previousTileSize = tileSize;
    ImGui::InputInt("Wielkosc kafelkow w atlasie", &tileSize, 32, 64);
    if(tileSize < 1 || tileSize > 256 || tileSize % 32 != 0) tileSize = im_previousTileSize; //checking if tile size provided by user is multiple of 32 etc.
    
    if(tileSize != im_previousTileSize) {
        m_levelConfig.setTileSize(tileSize);
        m1.createGrid();
        m1.createMap();
        setUpTileList(m1);
    }
    //set tileatlas tile size

    std::string im_atlasFilePath = tileAtlasFilePath.generic_string();
    ImGui::InputText("Sciezka do atlasu kafelkow", &im_atlasFilePath, 128);
    tileAtlasFilePath = im_atlasFilePath;

    uint32_t row = 0;
    for(uint32_t i = 0; const auto& t: m_tilesRectList) {
        ++i;
        ImGui::PushID(i);
         
        if(ImGui::ImageButton(t.getSprite(m1.getTileAtlasTexture()), 0)) {
            m_selectedTile = t;
            m_selectedTile.isSelected(true);
        }
        
        ImGui::PopID();
        if((i % tileAtlasColumns) != 0) {
            ImGui::SameLine(); 
        } else {
            ++row;
        }
    }
    
}

void EditorGui::updateSelectedTilePosition() {
    if(m_selectedTile.isSelected() && 
                ImGui::GetMousePos().x >= 0 && ImGui::GetMousePos().x <= 1024 && 
                ImGui::GetMousePos().y >= 0 && ImGui::GetMousePos().y <= 768) {
        
        uint32_t tileAtlasTileSize = m_levelConfig.getTileSize();
        //TO DO rename variables here
        uint32_t ex = floor(ImGui::GetMousePos().x / static_cast<float>(tileAtlasTileSize));
        uint32_t ey = floor(ImGui::GetMousePos().y / static_cast<float>(tileAtlasTileSize));
        m_selectedTile.setPosition(ex, ey);
    }
    

}


void EditorGui::placeTile(Map &m1) {
    m1.updateTile(m_selectedTile);
    m_selectedTile.isSelected(false);
   
}


void EditorGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    
    if(m_selectedTile.isSelected()) {
        target.draw(m_selectedTile, states); 
    }
}