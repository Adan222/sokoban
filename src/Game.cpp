#include "Game.hpp"
#include "states/LevelEditorState.hpp"
#include "states/MainMenuState.hpp"
#include "states/PlayingState.hpp"
#include <SFML/Window/Mouse.hpp>

Game::Game() :
    m_window(sf::VideoMode{1024, 768}, "Sokoban - MSC", sf::Style::Close),
    m_fps(getWindowWidth())
{    
    m_window.setFramerateLimit(60);
    ImGui::SFML::Init(m_window); //must be here
}

void Game::run() {
    pushState(std::make_unique<State::MainMenuState>(*this));

    // ticks per seconds
    sf::Time fpc = sf::seconds(1.0f / 30.0f);
    sf::Clock clock;
    sf::Time lastTime{sf::Time::Zero};
    sf::Time lag{sf::Time::Zero};

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
            state.update(lag, true);
        }

        //update
        state.update(elapsed);
        m_fps.update(elapsed.asSeconds());

  
        //draw
        m_window.clear();
        state.draw(m_window);
        m_window.draw(m_fps);
        m_window.display();

        //handle event last, because of exceptions
        handleEvent();
    }

}

State::State& Game::getCurrentState() const {
    return *(m_states.back());
}


sf::View Game::getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
    view.zoom(.9f);

    return view;
}

void Game::handleEvent() {
    sf::Event e;

    while(m_window.pollEvent(e)) {
        if(!m_states.empty()) { // needed, othwerwise segmentation fault
            getCurrentState().handleEvent(e);
        }
        sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
        switch(e.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::Resized:
                   
                   //_window.setView(getLetterboxView( m_window.getView(), e.size.width, e.size.height ));

                
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

sf::RenderWindow &Game::getWindow() {
    return m_window;
}

Game::~Game() {}