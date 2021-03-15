#include "PlayingState.hpp"

namespace State {

PlayingState::PlayingState(Game& game) : State(game),
    m_player(game.getWindowWidth() / 2, game.getWindowHeight() / 2),
    m_level(std::string(LEVEL_CONFIG_DIR) + "test.json")
{

}


void PlayingState::draw(sf::RenderTarget& renderer) {
    renderer.draw(m_player);
    m_level.render(renderer);
}

void PlayingState::handleEvent(sf::Event e) {
    if(e.type == sf::Event::KeyPressed){
        //enter menu
        if(e.key.code == sf::Keyboard::Escape)
            m_game.pushState(std::make_unique<MainMenuState>(m_game));
    }
}

void PlayingState::update(float deltaTime){
    m_player.input();
    m_player.update(deltaTime);
}

void PlayingState::pause() {

}

void PlayingState::resume(){
    
}

PlayingState::~PlayingState() {
    
}

} // namespace State
