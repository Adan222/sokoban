#include "MainMenuState.hpp"

namespace State {


MainMenuState::MainMenuState(Game &game) :
    State(game),
    m_pageWantExit(false)
{
    /**
     * We have to reserve elemnts in vector
     * couse we can`t copy WidgetStack
     */
    m_pages.reserve(10);

    createMenuPage();
}

MainMenuState::~MainMenuState() {}

uint32_t MainMenuState::getCurrentPage() const {
    return m_pages.size()-1;
}

void MainMenuState::pushPage() {
    m_pages.emplace_back(WidgetStack(m_game.getWindow()));
}

void MainMenuState::popPage() {
    if(!m_pages.empty())
        m_pages.pop_back();
}

void MainMenuState::draw(sf::RenderTarget &renderer) {
    if(!m_pageWantExit)
        renderer.draw(m_pages[getCurrentPage()]);
}

void MainMenuState::update(const float deltaTime) {

}

void MainMenuState::handleEvent(sf::Event e) {
    if(e.type == sf::Event::KeyPressed){
        switch (e.key.code) {
            case sf::Keyboard::Escape:
                m_game.exit();
                break;
            default:
                break;
        }   
    }
    if(e.type == sf::Event::MouseButtonPressed){
        m_pages[getCurrentPage()].handleEvent(e);
    }

    if(m_pageWantExit){
        popPage();
        m_pageWantExit = false;
    }
}

}   //namespace State