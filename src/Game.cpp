#include "Game.hpp"

Game::Game() :
    m_window(sf::VideoMode{1200, 700}, "Sokoban:d")
{
    pushState(std::make_unique<State::PlayingState>());
    m_window.setFramerateLimit(60);

    m_window_size = m_window.getSize();
}

void Game::run() {
    while (m_window.isOpen() && !m_states.empty()) {
        auto &state = getCurrentState();

        m_window.clear();
        
        state.draw(m_window);
        m_window.display();

        handleEvent();
        if(state.wantTerminateSelf()) popState();
    }
}


State::State& Game::getCurrentState() const {
    return *(m_states.back());
}

void Game::pushState(std::unique_ptr<State::State>state) {
    m_states.push_back(std::move(state));
}

void Game::handleEvent() {
    sf::Event e;
    while(m_window.pollEvent(e)) {
        getCurrentState().handleEvent(e);
        switch(e.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            default:
                break;
        }
    }
}

void Game::popState() {
    m_states.pop_back();
}

Game::~Game() {

}