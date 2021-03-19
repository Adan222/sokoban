#include "Level.hpp"

Level::Level(const std::string& filename) : 
    m_levelConfig(filename),
    m_box(700, 300),
    m_player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)
{   
    m_t1.createMap(m_levelConfig);
}

Level::~Level() {}

void Level::render(sf::RenderTarget& renderer) {
    renderer.draw(m_t1);
    renderer.draw(m_player);
    renderer.draw(m_box);
}

void Level::input(sf::Keyboard::Key k){
    m_player.handleInput(k);
}

void Level::update(const float deltaTime){
    m_player.update(deltaTime);
}
