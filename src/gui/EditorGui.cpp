#include "EditorGui.hpp"
#include <SFML/Graphics.hpp>
#include "map/Map.hpp"
#include <nfd.h>
#include "ImGuiStyle.hpp"


EditorGui::EditorGui(LevelConfig& levelConfig, bool initialPopupShowed) :       
        m_levelConfig(levelConfig),
        m_liftedTile(m_levelConfig.get().getTileSize()),
        m_openPath(levelConfig.getJsonFilePath()),
        m_initialPopupShowed(initialPopupShowed),
        m_reload(false),
        m_selectedTile(nullptr)
{
    ImGui::Style::Load();
    ImGui::SFML::UpdateFontTexture(); 

    m_savePath = m_openPath;
}




EditorGui::~EditorGui() {}


void EditorGui::setUpTileList(Map& m1) {
    const uint32_t tileSize = m_levelConfig.get().getTileSize();
    sf::Texture tileAtlasTexture = m1.getTileAtlasTexture();
    sf::Vector2u tileAtlasTextureSize = tileAtlasTexture.getSize();
    const uint32_t tileAtlasColumns = m1.getTileAtlasColumns();
    const uint32_t numberOfTiles = (tileAtlasTextureSize.x  + 1)/ tileSize * (tileAtlasTextureSize.y  + 1) / tileSize;
    //to do number of tile in map function


    uint32_t row = 0, column = 0, actualTileTextureID = 0;
    float scale = 28.0f / static_cast<float>(tileSize);

    m_tilesRectList.clear();
    m_tilesRectList.resize(numberOfTiles, Tile(tileSize));

    for(auto &t : m_tilesRectList) {
        if(column % tileAtlasColumns == 0 && actualTileTextureID != 0) {
            column = 0;
            ++row;
        }
        t.setTextureCoords(column, row, actualTileTextureID);
        t.setScale(scale, scale);
        ++actualTileTextureID;
        ++column;
    }

}



void EditorGui::mainPanel(Map& m1) {
    initialPrompt();

    ImGui::Begin("Ustawienia", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    if(ImGui::BeginTabBar("E", ImGuiTabBarFlags_Reorderable)) {
        if(ImGui::BeginTabItem("Lista kafelkow")) {
            tileList(m1);
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("Opcje kafelka")) {
            tileOptions();
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("Opcje mapy")) {
            mapSettings(m1);
            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }
    
    ImGui::End();
}


void EditorGui::tileList(Map& m1) {
    std::filesystem::path tileAtlasFilePath = m_levelConfig.get().getTileAtlasPath();
    uint32_t tileAtlasColumns =  m1.getTileAtlasColumns();
    int tileSize = m_levelConfig.get().getTileSize(); //using int, because imgui is not supporting uint32_t
    

    //tile size
    uint32_t im_previousTileSize = tileSize;
   
    ImGui::Text("Wielkosc kafelkow w atlasie"); ImGui::SameLine();
    ImGui::InputInt("", &tileSize, 32, 64);
    if(tileSize < 1 || tileSize > 256 || tileSize % 32 != 0) tileSize = im_previousTileSize; //checking if tile size provided by user is multiple of 32 etc.
    if(tileSize != im_previousTileSize) {
        m_levelConfig.get().setTileSize(tileSize);
        m_reload = true;
    }
 

    //tile atlas path
    ImGui::Text("Sciezka do atlasu kafelkow"); ImGui::SameLine();
    std::string toshow = tileAtlasFilePath.generic_string();
    ImGui::InputText("", &toshow, ImGuiInputTextFlags_ReadOnly); ImGui::SameLine();
    if(ImGui::Button("...")) {
        nfdchar_t* tempPath = nullptr;
        if(NFD_OpenDialog("png", NULL, &tempPath) == NFD_OKAY) { 
            m_levelConfig.get().setTileAtlasFilePath(tempPath);
            m_reload = true;
        }
    }


    uint32_t row = 0;
    for(uint32_t i = 0; const auto& t: m_tilesRectList) {
        ++i;
        ImGui::PushID(i);
        if(ImGui::ImageButton(t.getSprite(m1.getTileAtlasTexture()), 0)) {
            m_liftedTile = t;
            m_liftedTile.isSelected(true);
        }
        ImGui::PopID();
        if((i % tileAtlasColumns) != 0) 
            ImGui::SameLine(); 
        else 
            ++row;
    }
    
    
}

void EditorGui::tileOptions() {
    if(m_selectedTile != nullptr) {
        int e = m_selectedTile->getLogicID();

        ImGui::RadioButton("Tlo", &e, 0); 
        ImGui::RadioButton("Sciana", &e, 1);
        ImGui::RadioButton("Pozycja poczatkowa gracza", &e, 2);
        ImGui::RadioButton("Box", &e, 3); 
        ImGui::RadioButton("Miejsce wygrania", &e, 4);  
        ImGui::RadioButton("Miejsce wygrania wraz z boxem", &e, 5); 
        if(e != m_selectedTile->getLogicID()) {
            m_selectedTile->setLogicID(e);
        }
    } else {
        ImGui::Text("No tile selected");
    }

}

void EditorGui::openFileDialog() {
    nfdchar_t* tempPath = nullptr;
    if(NFD_OpenDialog("json", NULL, &tempPath) == NFD_OKAY) {
        std::filesystem::path temp = tempPath;
        if(LevelConfig::validateJSON(temp)) {
            m_levelConfig.get().setJsonFilePath(temp);
            m_initialPopupShowed = true;
            m_reload = true;
            ImGui::CloseCurrentPopup();
        } else {
            ImGui::OpenPopup("Blad");
        }
    }
}

void EditorGui::saveFileDialog(Map& m1) {
    nfdchar_t* tempPath = nullptr;
    
    if(NFD_SaveDialog("json", NULL, &tempPath) == NFD_OKAY) {
       m_savePath = tempPath;
       m1.saveGrids();
       m_levelConfig.get().saveToFile(tempPath);
    }
}


void EditorGui::mapSettings(Map& m1) {
    if(ImGui::Button("Otworz")) 
        openFileDialog();

    ImGui::SameLine();
    if(ImGui::Button("Zapisz")) {
        if(m_savePath == "") {
            saveFileDialog(m1);
        } else {
            m1.saveGrids();
            m_levelConfig.get().saveToFile(m_savePath);
        }
    } ImGui::SameLine();
   

    if(ImGui::Button("Zapisz jako")) 
        saveFileDialog(m1);
    
    
    
    int a = 0;
    ImGui::SliderInt("Przyblizenie mapy: ", &a, 100, 255);
    
    errorFileLoading(); //it shows only on call, must be here
}

void EditorGui::errorFileLoading() {
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize({400, 80});
    
    if(ImGui::BeginPopupModal("Blad")) {
        ImGui::TextWrapped("Wystapil blad podczas ladowania pliku json.");
        ImGui::SetCursorPos({300, 50});
        if(ImGui::Button("Ok")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}



std::filesystem::path& EditorGui::getOpenPath() {
    return m_openPath;
}

bool EditorGui::wantsReload() const {
    return m_reload;
}

void EditorGui::initialPrompt() {
    if(!m_initialPopupShowed) {
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize({300,150});
        ImGui::OpenPopup("Chcesz zaladowac istniejaca mape?");
    }

    if (ImGui::BeginPopupModal("Chcesz zaladowac istniejaca mape?")) {
        if(ImGui::Button("Wybierz plik")) {
            openFileDialog();
        }
        ImGui::SameLine(); 
        if(ImGui::Button("Nowy")) {
            ImGui::CloseCurrentPopup();
            m_initialPopupShowed = true;
        }

        errorFileLoading(); //it shows only when called, must be here
        ImGui::EndPopup();
    }

  
}



void EditorGui::updateSelectedTilePosition() {
    if(m_liftedTile.isSelected() && 
                ImGui::GetMousePos().x >= 0 && ImGui::GetMousePos().x <= 1024 && 
                ImGui::GetMousePos().y >= 0 && ImGui::GetMousePos().y <= 768) {
        
        uint32_t tileAtlasTileSize = m_levelConfig.get().getTileSize();
        //TO DO rename variables here
        uint32_t ex = floor(ImGui::GetMousePos().x / static_cast<float>(tileAtlasTileSize));
        uint32_t ey = floor(ImGui::GetMousePos().y / static_cast<float>(tileAtlasTileSize));
        m_liftedTile.setPosition(ex, ey);
    }
}


void EditorGui::placeTile(Map& m1) {
    if(m_liftedTile.isSelected()) {
        m1.updateTile(m_liftedTile);
        m_liftedTile.isSelected(false);
    }
}

void EditorGui::selectTile(Map& m1 ,sf::Vector2f mousePosition) {
    if(!m_liftedTile.isSelected()) {
        m1.unselectTile(m_selectedTile);
        m_selectedTile = m1.selectTile(mousePosition);
    }
}




void EditorGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    if(m_liftedTile.isSelected()) {
        target.draw(m_liftedTile, states); 
    }
}
