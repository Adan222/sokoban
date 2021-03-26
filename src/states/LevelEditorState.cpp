#include "LevelEditorState.hpp"
#include "imgui-SFML.h"


namespace State {



LevelEditorState::LevelEditorState(Game &game) :  State(game), m_editor(m_levelConfig, false) {
    m_jsonPath.generic_string() = "";

}



void LevelEditorState::draw(sf::RenderTarget &renderer) {
    m_editor.render(renderer);

}

void LevelEditorState::update(float deltaTime) {

    m_editor.update(deltaTime, m_jsonPath);
                                     
    if(m_jsonPath.generic_string() != "") {
        m_levelConfig = LevelConfig(m_jsonPath);
        m_editor = LevelEditor(m_levelConfig, true);
        m_jsonPath = "";
    }
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
