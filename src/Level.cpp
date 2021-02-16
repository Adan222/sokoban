#include <Level.hpp>


Level::Level(const std::string& filename) : m_levelConfigStream(filename) {
    if(!m_levelConfigStream)
        throw std::runtime_error(filename + ": " + std::strerror(errno));
    
    m_levelConfigStream >> m_levelConfig;

    m_t1.createMap(m_levelConfig);
}

void Level::render(sf::RenderTarget& renderer) {
    renderer.draw(m_t1);
}

Level::~Level() {

}