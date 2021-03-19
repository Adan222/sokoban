#include "PlayingState.hpp"

namespace State {

PlayingState::PlayingState(Game& game) : 
    State(game),
    m_level("../res/level_configs/test.json")
{}


void PlayingState::draw(sf::RenderTarget& renderer) {
    m_level.render(renderer);
}

void PlayingState::handleEvent(sf::Event e) {
    using Key = sf::Keyboard;

    if(e.type == sf::Event::KeyPressed){
        //enter menu
        if(e.key.code == Key::Escape)
            m_game.pushState(std::make_unique<MainMenuState>(m_game));
        else
            m_level.input(e.key.code);
    }
}

void PlayingState::update(const float deltaTime){
    m_level.update(deltaTime);
}

PlayingState::~PlayingState() {
    
}

} // namespace State
