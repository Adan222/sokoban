#include "PlayingState.hpp"

namespace State {

PlayingState::PlayingState(Game& game) : State(game),
    //m_player(game.getWindowWidth()/2, game.getWindowHeight()/2, 30.0f),
    m_level("../src/level_configs/test.json")
{

}


void PlayingState::draw(sf::RenderTarget& renderer) {
    //renderer.draw(m_player);
    m_level.render(renderer);
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
