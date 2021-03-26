#include "LevelEditor.hpp"


LevelEditor::LevelEditor(LevelConfig levelConfig, bool initialPopupShowed) 
    : m_levelConfig(levelConfig), m_m1(m_levelConfig), m_editorGui(m_levelConfig)
{
    m_m1.loadTexture();
    m_m1.createMap();
    m_m1.createGrid();
    m_editorGui.initialPopupShowed(initialPopupShowed);
    m_editorGui.setUpTileList(m_m1);

    m_attachedTextureRS.texture = &m_m1.getTileAtlasTexture();
}


LevelEditor::~LevelEditor()
{
    
}

void LevelEditor::render(sf::RenderTarget& renderer) {
    m_editorGui.header();
    m_editorGui.mainPanel(m_m1);
    
    renderer.draw(m_m1);
    renderer.draw(m_editorGui, m_attachedTextureRS);
}

void LevelEditor::update(const float deltaTime, std::filesystem::path& jsonPath) {
    m_editorGui.updateSelectedTilePosition();
    jsonPath = m_editorGui.getNewConfigPath();
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

