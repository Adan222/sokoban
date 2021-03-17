#include "LevelEditorState.hpp"


namespace State {

LevelEditorState::LevelEditorState(Game &game) :  State(game), m_levelConfig("../res/level_configs/default.json") {
    m_m1.createMap(m_levelConfig);
    m_tileAtlasTexture = m_m1.getTileAtlasTexture();

    m_atlasTileSize = m_levelConfig.getTileAtlasTileSize();
    m_atlasFilePath = m_levelConfig.getTileAtlasPath();

    setUpTileRectList();
}

void LevelEditorState::setUpTileRectList() {
    sf::Vector2u tileAtlasSize = m_tileAtlasTexture.getSize();
    uint32_t numberOfTiles = (tileAtlasSize.x / m_atlasTileSize) * (tileAtlasSize.y / m_atlasTileSize);

    m_tilesRectList.resize(numberOfTiles, sf::Sprite(m_tileAtlasTexture));

    for(auto & t : m_tilesRectList) {
        t.setTextureRect(sf::IntRect(sf::Vector2i(m_atlasTileSize, 0), sf::Vector2i(m_atlasTileSize, m_atlasTileSize)));
    }
}


void LevelEditorState::initValuesFromJSON() {
   
}


void LevelEditorState::draw(sf::RenderTarget &renderer) {
    tileSelectionBox();
    renderer.draw(m_m1);
}

void LevelEditorState::tileSelectionBox() {
    ImGui::Begin("Lista kafelków", NULL, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Plik")) {
            if (ImGui::MenuItem("Otwórz inny plik z kafelkami", "Ctrl+O")) { /* Do stuff */ }
            ImGui::EndMenu();
        }
    }
    ImGui::EndMenuBar();
        
    //int frame_padding = -1 + i;                             // -1 == uses default padding (style.FramePadding)
    //ImVec2 size = ImVec2(32.0f, 32.0f);                     // Size of the image we want to make visible
    //ImVec2 uv0 = ImVec2(0.0f, 0.0f);                        // UV coordinates for lower-left
    //ImVec2 uv1 = ImVec2(32.0f / my_tex_w, 32.0f / my_tex_h);// UV coordinates for (32,32) in our texture
    //ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);         // Black background
    //ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);       // No tint
    //if (ImGui::ImageButton(my_tex_id, size, uv0, uv1, frame_padding, bg_col, tint_col))



    uint16_t im_previousAtlasTileSize =  m_atlasTileSize;
    ImGui::InputInt("Wielkosc kafelkow w atlasie", &m_atlasTileSize, 32, 64);
    if(m_atlasTileSize < 1 || m_atlasTileSize > 256 || m_atlasTileSize % 32 != 0) m_atlasTileSize = im_previousAtlasTileSize; //checking if tile size provided by user is multiple of 32 etc.
    
    std::string im_atlasFilePath = m_atlasFilePath.generic_string();
    ImGui::InputText("Sciezka do atlasu kafelkow", &im_atlasFilePath, 128);
    m_atlasFilePath = im_atlasFilePath;


    //
   
    //

    ImGui::ImageButton(m_tileAtlasTexture, 0);
    //ImGui::ImageButton()
    ImGui::End();
}


void LevelEditorState::handleEvent(sf::Event e) {
    ImGui::SFML::ProcessEvent(e);

    if(e.type == sf::Event::KeyPressed){
        switch (e.key.code) {
            case sf::Keyboard::Escape:
                m_game.popState();
                break;
            default:
                break;
        }   
    }

}

void LevelEditorState::pause() {

}

void LevelEditorState::resume() {
    
}

LevelEditorState::~LevelEditorState(){

}


}   //namespace State
