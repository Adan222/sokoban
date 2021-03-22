#pragma once
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>
#include "LevelConfig.hpp"
#include "Tile.hpp"

class Map : public sf::Drawable, public sf::Transformable {
    const LevelConfig& m_levelConfig;
    
    sf::Texture m_tileAtlas;
    std::vector<Tile> m_tiles;
    std::vector<sf::RectangleShape> m_gridSquares;


    uint64_t convertPositionToIndex(sf::Vector2u position2D);
public:
    sf::Texture& getTileAtlasTexture();
    uint32_t getTileAtlasColumns();

    void createMap();
    void createGrid();
    void updateTile(Tile& selectedTile);
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Map(LevelConfig& levelConfig);
    ~Map();

};