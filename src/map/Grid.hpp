#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "level/LevelConfig.hpp"

class Grid : public sf::Drawable, public sf::Transformable {
    std::vector<sf::RectangleShape> m_gridSquares;
    std::vector<sf::FloatRect> m_gridSquaresBounds;
public:
    std::vector<sf::FloatRect>& getGridSquaresBounds() ;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Grid(const LevelConfig &levelConfig);
    ~Grid();
};