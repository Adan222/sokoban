#include "LevelEditorState.hpp"


namespace State {

LevelEditorState::LevelEditorState(Game &game) :  State(game), m_levelConfig("../res/level_configs/default.json") {
    m_m1.createMap(m_levelConfig);

    m_tileAtlasTexture = m_m1.getTileAtlasTexture();
    m_atlasTileSize = m_levelConfig.getTileAtlasTileSize();
    m_atlasFilePath = m_levelConfig.getTileAtlasPath();
    m_tileAtlasFileTxtSize = m_tileAtlasTexture.getSize();
    m_tileAtlasColumns = m_levelConfig.getTileAtlasColumns();

    setUpTileRectList();
}

void LevelEditorState::setUpTileRectList() {
    uint32_t row = 0, column = 0, actualTileID = 0;
    uint32_t numberOfTiles = (m_tileAtlasFileTxtSize.x / m_atlasTileSize) * (m_tileAtlasFileTxtSize.y / m_atlasTileSize);
    float scale = 32.0f / static_cast<float>(m_atlasTileSize);

    m_tilesRectList.resize(numberOfTiles, sf::Sprite(m_tileAtlasTexture));
    for(auto &t : m_tilesRectList) {
        if(column * m_atlasTileSize >= (m_tileAtlasFileTxtSize.x + 1)) {
            column = 0;
            ++row;
        }
        t.setTextureRect(sf::IntRect(sf::Vector2i(column * m_atlasTileSize, row * m_atlasTileSize), sf::Vector2i(m_atlasTileSize, m_atlasTileSize)));
        t.setScale(scale, scale);
        ++actualTileID;
        ++column;
    }
}

void LevelEditorState::mainPanel() {
    
    ImGui::Begin("Lista kafelków", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Plik")) {
            if (ImGui::MenuItem("Otwórz inny plik z kafelkami", "Ctrl+O")) { /* Do stuff */ }
            ImGui::EndMenu();
        }
    }
    ImGui::EndMenuBar();
    tileSelectionBox();
    ImGui::End();
}

void LevelEditorState::draw(sf::RenderTarget &renderer) {
    mainPanel();
    renderer.draw(m_m1);
    renderer.draw(m_selectedTile);
}

void LevelEditorState::tileSelectionBox() {
    uint16_t im_previousAtlasTileSize =  m_atlasTileSize;
    ImGui::InputInt("Wielkosc kafelkow w atlasie", &m_atlasTileSize, 32, 64);
    if(m_atlasTileSize < 1 || m_atlasTileSize > 256 || m_atlasTileSize % 32 != 0) m_atlasTileSize = im_previousAtlasTileSize; //checking if tile size provided by user is multiple of 32 etc.
    
    std::string im_atlasFilePath = m_atlasFilePath.generic_string();
    ImGui::InputText("Sciezka do atlasu kafelkow", &im_atlasFilePath, 128);
    m_atlasFilePath = im_atlasFilePath;

    for(int i = 0; const auto& t: m_tilesRectList) {
        ++i;
        ImGui::PushID(i);
        if(ImGui::ImageButton(t, 0)) {
            std::cout<< "CLICKED" << std::endl;
            tileSelected(t);
        }
        
        ImGui::PopID();
        if((i % m_tileAtlasColumns) != 0) {
            ImGui::SameLine();
        }
    }
    
}


void LevelEditorState::tileSelected(const sf::Sprite& ts) {
    m_selectedTile = ts;
    m_selectedTile.setPosition(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
}


void LevelEditorState::update(float deltaTime) {
    m_selectedTile.setPosition(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
}

void LevelEditorState::handleEvent(sf::Event e) {
    ImGui::SFML::ProcessEvent(e);

    if(e.type == sf::Event::KeyPressed){
        switch (e.key.code) {
            case sf::Keyboard::Escape:
                m_game.popState();
                break;
            case sf::Mouse::Right:
                m_selectedTile = sf::Sprite{};
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
