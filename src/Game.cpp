#include <cstddef>
#include "SFML/System/Vector2.hpp"

#include "Game.hpp"
#include "states/MainMenuState.hpp"

Game::Game() :
    m_window(sf::VideoMode{1024, 768}, "Sokoban:d")
{    
    ImGui::SFML::Init(m_window);
    m_window.setFramerateLimit(60);
    m_window_size = m_window.getSize();
}

void Game::run() {
    sf::Clock deltaClock;
   
    pushState(std::make_unique<State::LevelEditorState>(*this));

    m_window.resetGLStates(); //temporary, needed only if we dont draw SFML things

    while (m_window.isOpen() && !m_states.empty()) {
        auto &state = getCurrentState();
        ImGui::SFML::Update(m_window, deltaClock.restart());
               
        
        m_window.clear();
        state.draw(m_window);
        ImGui::SFML::Render(m_window);
        m_window.display();
        handleEvents();
    }

    ImGui::SFML::Shutdown();
}


State::State& Game::getCurrentState() const {
    return *(m_states.back());
}

void Game::handleEvents() {
    sf::Event e;
    while(m_window.pollEvent(e)) {
        if(!m_states.empty()) { // needed, othwerwise segmentation fault
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