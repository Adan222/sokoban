#include "LevelEditorState.hpp"


namespace State {

LevelEditorState::LevelEditorState(Game &game) :  State(game), m_m1(m_levelConfig), m_editorGui(m_levelConfig) {

   m_m1.loadTexture();
    m_m1.createMap();
    m_m1.createGrid();
    m_editorGui.setUpTileList(m_m1);
    
}


void LevelEditorState::draw(sf::RenderTarget &renderer) {
    sf::RenderStates s;
    s.texture = &m_m1.getTileAtlasTexture();
    
    
    m_editorGui.header();
    m_editorGui.mainPanel(m_m1);
    
    renderer.draw(m_m1);
    renderer.draw(m_editorGui, s);
}




void LevelEditorState::update(float deltaTime) {
    m_editorGui.updateSelectedTilePosition();
}

void LevelEditorState::handleEvent(sf::Event e) {
    ImGui::SFML::ProcessEvent(e);
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(!ImGui::IsAnyItemHovered()) {
            m_editorGui.placeTile(m_m1); 
            m_editorGui.selectTile(m_m1, ImGui::GetMousePos());   
        } 
        
    }
    
   

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
