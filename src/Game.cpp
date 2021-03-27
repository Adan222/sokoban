#include "Game.hpp"
#include "states/LevelEditorState.hpp"
#include "states/MainMenuState.hpp"
#include "states/PlayingState.hpp"
#include <SFML/Window/Mouse.hpp>

Game::Game() :
    m_window(sf::VideoMode{1024, 768}, "Sokoban:D"),
    m_fps(getWindowWidth())
{    
    m_window.setFramerateLimit(60);
    ImGui::SFML::Init(m_window);
}

void Game::run() {
    //----------------------
    //TODO:
    // - move imgui to LevelEditorState 
    //----------------------
   
    pushState(std::make_unique<State::LevelEditorState>(*this));

    // ticks per seconds
    sf::Time fpc = sf::seconds(1.0 / 30.0f);

    sf::Clock clock;

    sf::Time lastTime = sf::Time::Zero;
    sf::Time lag = sf::Time::Zero;

    while (m_window.isOpen() && !m_states.empty()) {
        auto &state = getCurrentState();

        //Time
        sf::Time currTime = clock.getElapsedTime();
        sf::Time elapsed = currTime - lastTime;
        lastTime += elapsed;
        lag += elapsed;

        //Fixed time update
        while(lag > fpc){
            lag -= fpc;
            state.update(lag.asSeconds());

        }

        //Update
        state.update(elapsed.asSeconds());
        m_fps.update(elapsed.asSeconds());
        ImGui::SFML::Update(m_window, elapsed);

  
        //Draw
        m_window.clear();

        state.draw(m_window);
        m_window.draw(m_fps);
        ImGui::SFML::Render(m_window);

        m_window.display();

        //Event
        handleEvent();
    }

    ImGui::SFML::Shutdown();
}

State::State& Game::getCurrentState() const {
    return *(m_states.back());
}

void Game::handleEvent() {
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

void Game::exit(){
    m_window.close();
}

sf::Vector2u Game::getWindowSize() const {
    return m_window.getSize();
}

uint32_t Game::getWindowWidth() const {
    return m_window.getSize().x;
}

uint32_t Game::getWindowHeight() const {
    return m_window.getSize().y;
}

sf::Vector2i Game::getMousePos() const {
    return sf::Mouse::getPosition(m_window);
}

const sf::RenderWindow &Game::getWindow() const {
    return m_window;
}

Game::~Game() {}