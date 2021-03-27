#include "LevelEditorState.hpp"
#include "imgui-SFML.h"


namespace State {



LevelEditorState::LevelEditorState(Game &game) :  State(game), m_editor(m_levelConfig) {
    
}


void LevelEditorState::draw(sf::RenderTarget &renderer) {
    m_editor.render(renderer);
}

void LevelEditorState::update(float deltaTime) {
    m_editor.update(deltaTime);
                                     
    if(m_levelConfig.isNewConfigPathSet()) {
        auto newOpenPath = m_levelConfig.getJsonFilePath();
        m_levelConfig = LevelConfig(newOpenPath);
    }
    
    if(m_editor.wantsReload())
        m_editor = LevelEditor(m_levelConfig, true);
    
}

void LevelEditorState::handleEvent(sf::Event e) {
    m_editor.input(e);
}

void LevelEditorState::pause() {

}

void LevelEditorState::resume() {
    
}

LevelEditorState::~LevelEditorState(){

}


}   //namespace State
