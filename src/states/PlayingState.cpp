#include "PlayingState.hpp"

namespace State {

PlayingState::PlayingState(Game& game) : State(game),
    m_player(game.getWindowWidth() / 2, game.getWindowHeight() / 2),
    m_level("../res/level_configs/test.json")
{

}


void PlayingState::draw(sf::RenderTarget& renderer) {
    renderer.draw(m_player);
    m_level.render(renderer);
}

void PlayingState::handleEvent(sf::Event e) {
    using Key = sf::Keyboard;

    if(e.type == sf::Event::KeyPressed){
        //enter menu
        if(e.key.code == Key::Escape)
            m_game.pushState(std::make_unique<MainMenuState>(m_game));
        else if(e.key.code == Key::W || 
                e.key.code == Key::A ||
                e.key.code == Key::S ||
                e.key.code == Key::D )
            m_player.handleInput(e.key.code);
    }
}

void PlayingState::update(float deltaTime){
    m_player.update(deltaTime);
}

PlayingState::~PlayingState() {
    
}

} // namespace State
