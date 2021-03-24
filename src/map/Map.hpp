#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <vector>
#include "level/LevelConfig.hpp"
#include "entities/Box.hpp"
#include "Tile.hpp"
#include "Grid.hpp"

class Map : public sf::Drawable, public sf::Transformable {
    const LevelConfig& m_levelConfig;
    
    sf::Texture m_tileAtlas;
    std::vector<Tile> m_tiles;
    std::vector<sf::RectangleShape> m_gridSquares;

    uint32_t convertPositionToIndex(sf::Vector2f position2D);
    sf::Vector2i indexToPos(u_int32_t index);

public:
    Map(const LevelConfig& levelConfig);
    ~Map();

    sf::Texture& getTileAtlasTexture();
    uint32_t getTileAtlasColumns();

    void createGrid();
    void updateTile(Tile& selectedTile);
    Tile* selectTile(sf::Vector2f mousePostion);
    void unselectTile(Tile* selectedTile);
    
    /*
     * Now class have referance to levelconfig
     * and we can`t use m_levelConfig in constructor.
     * When you bring something new just put it in initMap.
     */
    void initMap();

    /*
     * First call loadTexture then others
     */
    void loadTexture();
    void createMap();

    Positions find(LOGIC what,LOGIC sec = LOGIC_NONE);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};