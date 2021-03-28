#include "PlayingState.hpp"
#include <SFML/System/Time.hpp>
#include <memory>

namespace State {

PlayingState::PlayingState(Game& game) : 
    State(game),
    m_whichLvl(0),
    m_level("../res/levels/official/test.json")
{}

PlayingState::~PlayingState() {}


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

void PlayingState::update(const sf::Time deltaTime, bool fixed){
    m_level.update(deltaTime.asSeconds());
}

void PlayingState::setWhichLvl(const int which) {
    m_whichLvl = which;
}

} // namespace State
