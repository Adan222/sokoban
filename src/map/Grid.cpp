#include "Grid.hpp"

Grid::Grid(const LevelConfig &levelConfig) {
    m_gridSquares.resize(levelConfig.getMapMaxTilesAmount());

    uint32_t row = 0, column = 0;
    for(int i = 0; auto& square : m_gridSquares) {
        ++i;
        square.setSize(sf::Vector2f(levelConfig.getTileAtlasTileSize(), levelConfig.getTileAtlasTileSize()));
        square.setOutlineColor(sf::Color(255, 255, 255, 150));
        square.setFillColor(sf::Color::Transparent);
        square.setOutlineThickness(0.5);
        if(column == levelConfig.getMapWidth()) {
            column = 0;
            ++row;
        }
        square.setPosition(column * 64, row * 64);        
        ++column;
    }
}

Grid::~Grid() {

}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for(const auto& square : m_gridSquares) {
        target.draw(square);
    }
}


std::vector<sf::FloatRect>& Grid::getGridSquaresBounds()  {
    m_gridSquaresBounds.clear();
    if(!m_gridSquares.empty()) {
        m_gridSquaresBounds.reserve(m_gridSquares.size());
        for(const auto& square : m_gridSquares) { 
            m_gridSquaresBounds.push_back(square.getGlobalBounds());
        }
    }
    return m_gridSquaresBounds;
}
