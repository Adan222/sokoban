#include "MainMenuState.hpp"
#include "gui/menu/Button.hpp"
#include <memory>
#include <type_traits>

namespace State {

MainMenuState::MainMenuState(Game &game) :
    State(game),
    m_firstPage(game.getWindow())
{
    auto b = std::make_unique<Button>(WIDE);
    b->setString("Play");
    b->setPosition({100, 100});
    b->setFunction([&](){
        m_game.pushState(std::make_unique<PlayingState>(m_game));
    }
    );

    m_firstPage.addItem(std::move(b));

}

void MainMenuState::draw(sf::RenderTarget &renderer) {
    renderer.draw(m_firstPage);
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
        m_firstPage.handleEvent(e);
    }
}

MainMenuState::~MainMenuState(){

}


}   //namespace State