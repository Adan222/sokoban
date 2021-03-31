#include "LevelEditorState.hpp"
#include "imgui-SFML.h"
#include <SFML/Window/Keyboard.hpp>


namespace State {



LevelEditorState::LevelEditorState(Game &game) :  State(game), m_editor(m_levelConfig) {
    
}


void LevelEditorState::draw(sf::RenderTarget &renderer) {
    m_editor.render(renderer);
    ImGui::SFML::Render(m_game.getWindow());

}

void LevelEditorState::update(const sf::Time deltaTime, bool fixed) {
    m_editor.update(deltaTime.asSeconds());
                                     
    if(m_levelConfig.isNewConfigPathSet()) {
        auto newOpenPath = m_levelConfig.getJsonFilePath();
        m_levelConfig = LevelConfig(newOpenPath);
    }
    
    if(m_editor.wantsReload())
        m_editor = LevelEditor(m_levelConfig, true);
    
    if(!fixed)
        ImGui::SFML::Update(m_game.getWindow(), deltaTime);
}

void LevelEditorState::handleEvent(sf::Event e) {
    if(e.key.code == sf::Keyboard::Escape)
        wantExit();
    m_editor.input(e);
}

void LevelEditorState::pause() {

}

void LevelEditorState::resume() {
    
}

LevelEditorState::~LevelEditorState(){
    ImGui::SFML::Shutdown();

}


}   //namespace State
