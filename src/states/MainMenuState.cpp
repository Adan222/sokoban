#include "MainMenuState.hpp"
#include <chrono>

namespace State {

MainMenuState::MainMenuState(Game &game) :  State(game) {
    m_shape.setRadius(30.0f);
    m_shape.setFillColor(sf::Color::Red);
}

void MainMenuState::draw(sf::RenderTarget &renderer) {
    renderer.draw(m_shape);
}

void MainMenuState::handleEvent(sf::Event e) {
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

void MainMenuState::pause() {

}

void MainMenuState::resume(){
    
}

MainMenuState::~MainMenuState(){

}


}   //namespace State