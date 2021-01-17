#include "MainMenuState.hpp"
#include <chrono>

namespace State {

MainMenuState::MainMenuState(Game &game) :  State(game)
{
    m_shape.setRadius(30.0f);
    m_shape.setFillColor(sf::Color::Red);
}

void MainMenuState::draw(sf::RenderTarget &renderer)
{
    renderer.draw(m_shape);
}

void MainMenuState::handleEvent(sf::Event e)
{
    if(e.type == sf::Event::KeyPressed){
        if(e.key.code == sf::Keyboard::F){
            m_Game.pushState(std::make_unique<PlayingState>(m_Game));
        }
        if(e.key.code == sf::Keyboard::Escape) {
            std::cout << "mainmenuState esc!" << std::endl;
            m_Game.popState();
        }
    }
}

void MainMenuState::pause(){
    std::cout << "mainmenu pause\n";
    m_pauseTime = std::chrono::steady_clock::now();
}

void MainMenuState::resume(){
    std::cout << "resume mainmenu\n";

    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<float> dur = end - m_pauseTime;
    std::cout << "In pasue: " << dur.count() << "s\n";
}

MainMenuState::~MainMenuState(){

}


}   //namespace