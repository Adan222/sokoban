#include "Game.hpp"
#include "states/MainMenuState.hpp"
#include <cstddef>

Game::Game() :
    m_window(sf::VideoMode{800, 600}, "Sokoban:d")
{
    pushState(std::make_unique<State::MainMenuState>(*this));
    
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
    }
}


State::State& Game::getCurrentState() const {
    return *(m_states.back());
}

void Game::handleEvent() {
    sf::Event e;
    while(m_window.pollEvent(e)) {
        if(!m_states.empty()) { //(tymczasowy?) fix bo inaczej zrzut pamieci, moze jakby by było m_window.setKeyRepeatEnabled(false) to wtedy by nie wywalało, bo dostajemy kolejny event a m_states jest puste
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
    //pauzuje stejta
    if(!(countStates() == 0))
        getCurrentState().pause();
    m_states.push_back(std::move(state));
}

void Game::popState() {
    //musi sprawdzic przed popnieciem czy jest ostatni
    bool last = isLastState();

    m_states.pop_back();

    //odpazuzuj stata
    if(!last)
        getCurrentState().resume();
}

bool Game::isLastState() const{
    if(m_states.size() == 1)
        return true;
    else
        return false;
}

size_t Game::countStates() const{
    return m_states.size();
}

Game::~Game() {

}