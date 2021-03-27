#include "LevelEditor.hpp"


LevelEditor::LevelEditor(LevelConfig& levelConfig)
    : LevelEditor(levelConfig, false)
{}

LevelEditor::LevelEditor(LevelConfig& levelConfig, bool initialPopupShowed) 
    : m_levelConfig(levelConfig),
     m_m1(m_levelConfig),
     m_editorGui(m_levelConfig, initialPopupShowed)  
{
    m_m1.loadTexture();
    m_m1.createMap();
    m_m1.createGrid();
    m_editorGui.setUpTileList(m_m1);
}


LevelEditor::~LevelEditor() {
}

bool LevelEditor::wantsReload() const {
    return m_editorGui.wantsReload();
}

void LevelEditor::render(sf::RenderTarget& renderer) {
    m_attachedTextureRS.texture = &m_m1.getTileAtlasTexture();
    renderer.draw(m_m1);
    renderer.draw(m_editorGui, m_attachedTextureRS);
    m_editorGui.mainPanel(m_m1);
}

void LevelEditor::update(const float deltaTime) {
    m_editorGui.updateSelectedTilePosition();
}

void LevelEditor::input(sf::Event e) {
    ImGui::SFML::ProcessEvent(e);
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(!ImGui::IsAnyItemHovered()) {
            m_editorGui.placeTile(m_m1); 
            m_editorGui.selectTile(m_m1, ImGui::GetMousePos());   
        } 
        
    }
   
}

