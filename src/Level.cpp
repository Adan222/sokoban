#include "Level.hpp"

Level::Level(const std::string& filename) : m_levelConfig(filename),  m_t1(m_levelConfig)
{   
    m_t1.createMap(m_levelConfig);
}

void Level::render(sf::RenderTarget& renderer) {
    renderer.draw(m_t1);
}

Level::~Level() {

}