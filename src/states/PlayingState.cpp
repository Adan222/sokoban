#include "PlayingState.hpp"

namespace State {

//wywalilme konstruktor klasy level bo nie mam pliku
PlayingState::PlayingState(Game& game) : State(game),
    m_player(game.getWindowWidth()/2, game.getWindowHeight()/2, 30.0f)
{}


void PlayingState::draw(sf::RenderTarget& renderer) {
    renderer.draw(m_player);
}

void PlayingState::handleEvent(sf::Event e) {
    if (e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == sf::Keyboard::Escape) {
            m_Game.pushState(std::make_unique<MainMenuState>(m_Game));
        }
    }
}

void PlayingState::pause() {

}

void PlayingState::resume(){
    
}

PlayingState::~PlayingState() {
    
}

}   //namespace State
