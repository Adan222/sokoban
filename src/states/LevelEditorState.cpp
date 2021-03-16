#include "LevelEditorState.hpp"


namespace State {

LevelEditorState::LevelEditorState(Game &game) :  State(game), m_levelConfig("../res/level_configs/default.json") {
    m_m1.createMap(m_levelConfig);
    initValuesFromJSON();
}

void LevelEditorState::initValuesFromJSON() {
   
}


void LevelEditorState::draw(sf::RenderTarget &renderer) {
    tileSelectionBox();
    renderer.draw(m_m1);
}

void LevelEditorState::tileSelectionBox() {
    static int im_tileSize = 64;
    static char *im_atlasFilePath[128];

    ImGui::Begin("Lista kafelków", NULL, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Plik")) {
            if (ImGui::MenuItem("Otwórz inny plik z kafelkami", "Ctrl+O")) { /* Do stuff */ }
            ImGui::EndMenu();
        }
    }
    ImGui::EndMenuBar();
    
    uint16_t im_previousTileSize = im_tileSize;
    ImGui::InputInt("Wielkosc kafelkow w atlasie", &im_tileSize, 32, 64);
    if(im_tileSize < 1 || im_tileSize > 256 || im_tileSize % 32 != 0) im_tileSize = im_previousTileSize; //checking if tile size provided by user is multiple of 32 etc.
    atlasTileSize = im_tileSize;
    //ImGui::InputText("Sciezka do atlasu kafelkow: ", im_atlasFilePath, 128);
    //atlasFilePath = im_atlasFilePath;


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
