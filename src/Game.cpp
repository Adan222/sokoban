#include "Game.hpp"

Game::Game() : m_window(sf::VideoMode{1200,720}, "Sokoban:d") {
    pushState(std::make_unique<PlayingState>());
}

void Game::run() {
    while (m_window.isOpen()) {
        auto &state = getCurrentState();

        m_window.clear();

        state.eventHandler();
        state.draw(m_window);
        m_window.display();
    }
}


State& Game::getCurrentState() const {
    return *(m_states.back().get());
}

void Game::pushState(std::unique_ptr<State>state) {
    m_states.push_back(std::move(state));
}

Game::~Game() {

}