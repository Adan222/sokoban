#include <cstddef>
#include "SFML/System/Vector2.hpp"

#include "Game.hpp"
#include "states/MainMenuState.hpp"

Game::Game() :
    m_window(sf::VideoMode{800, 600}, "Sokoban:d")
{    
    m_window.setFramerateLimit(60);
    m_window_size = m_window.getSize();
}

void Game::run() {
    pushState(std::make_unique<State::PlayingState>(*this));

    while (m_window.isOpen() && !m_states.empty()) {
        auto &state = getCurrentState();
         
        m_window.clear();

        state.draw(m_window);
        m_window.display();

        handleEvent();
    }
}


State::State& Game::getCurrentState() const {
    return *(m_states.back());
}

void Game::handleEvent() {
    sf::Event e;
    while(m_window.pollEvent(e)) {
        if(!m_states.empty()) { // inaczej zrzut pamieci
            getCurrentState().handleEvent(e);
        }
        switch(e.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            default:
                break;
        }
    }
}

void Game::pushState(std::unique_ptr<State::State>state) {
    if(!m_states.empty())
        getCurrentState().pause();
    m_states.push_back(std::move(state));
}

void Game::popState() {
    m_states.pop_back();
    if(!m_states.empty())
        getCurrentState().resume();
}

sf::Vector2u Game::getWindowSize() const {
    return m_window_size;
}

int Game::getWindowWidth() const {
    return m_window_size.x;
}

int Game::getWindowHeight() const {
    return m_window_size.y;
}

Game::~Game() {

}