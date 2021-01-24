#include "PlayingState.hpp"
#include "states/MainMenuState.hpp"
#include <memory>

namespace State {

PlayingState::PlayingState(Game& game) : State(game),
                                         m_shape(30.0f),
                                         m_level("test.json") 
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
            std::cout << "palyingstate esc!" << std::endl;
            m_Game.popState();
        }
        if(e.key.code == sf::Keyboard::F) {
            m_Game.pushState(std::make_unique<MainMenuState>(m_Game));
        }

    }
}

void PlayingState::pause() {
    std::cout << "palyingstate pause\n";
    m_pauseTime = std::chrono::steady_clock::now();
}

void PlayingState::resume(){
    std::cout << "resume payingstate\n";

    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<float> dur = end - m_pauseTime;
    std::cout << "In pasue: " << dur.count() << "s\n";

}

PlayingState::~PlayingState() {
    
}

}
