#include "LevelEditorState.hpp"


namespace State {

LevelEditorState::LevelEditorState(Game &game) :  State(game) {
    
}

void LevelEditorState::draw(sf::RenderTarget &renderer) {
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::Button("SUCH WOW:D");
    ImGui::End();
}

void LevelEditorState::handleEvent(sf::Event e) {
    ImGui::SFML::ProcessEvent(e);

    if(e.type == sf::Event::KeyPressed){
        switch (e.key.code) {
            case sf::Keyboard::Escape:
                m_Game.popState();
                break;
            default:
                break;
        }   
    }
}

void LevelEditorState::pause() {

}

void LevelEditorState::resume(){
    
}

LevelEditorState::~LevelEditorState(){

}


}   //namespace State
