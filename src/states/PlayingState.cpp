#include "PlayingState.hpp"
#include "states/MainMenuState.hpp"
#include <memory>

namespace State {

//wywalilme konstruktor klasy level bo nie mam pliku
PlayingState::PlayingState(Game& game) : State(game), m_player(400.0f, 400.0f, 30.0f)
{}


void PlayingState::draw(sf::RenderTarget& renderer) {
    renderer.draw(m_player);
}

void PlayingState::handleEvent(sf::Event e) {
    if (e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == sf::Keyboard::Escape) {
            std::cout << "palyingstate esc!" << std::endl;
            m_Game.popState();
        }
        if(e.key.code == sf::Keyboard::F) {
            m_Game.pushState(std::make_unique<MainMenuState>(m_Game));
        }

    }
}

void PlayingState::pause() {
    std::cout << "playeingstate pause\n";
}

void PlayingState::resume(){
    std::cout << "playeingstate resume\n";
}

PlayingState::~PlayingState() {
    
}

}   //namespace State
