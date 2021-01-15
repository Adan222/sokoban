#include "PlayingState.hpp"

namespace State {

PlayingState::PlayingState(Game& game) : State(game),
                                         m_shape(30.0f) 
{
    m_shape.setFillColor(sf::Color::Green);
}


void PlayingState::draw(sf::RenderTarget& renderer) {
    renderer.draw(m_shape);
}

void PlayingState::handleEvent(sf::Event e) {
    if (e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == sf::Keyboard::Escape) {
            std::cout << "ESC PRESSED!" << std::endl;
            m_Game.popState();
        }
    }
}

PlayingState::~PlayingState() {
}

}
