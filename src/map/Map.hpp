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

    Positions m_boxesPos;
    Positions m_winPlaces;
    Positions m_walls;
    sf::Vector2i m_playerPos;

    uint32_t convertPositionToIndex(sf::Vector2f position2D);
    sf::Vector2i indexToPos(u_int32_t index);

    /*
     * Look for boxes and player
     */
    void findOn(const int index);

public:
    Map(const LevelConfig& levelConfig);
    ~Map();

    sf::Texture& getTileAtlasTexture();
    uint32_t getTileAtlasColumns();

    void createGrid();
    void updateTile(Tile& selectedTile);
    
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

    Positions getBoxesPos() const;
    Positions getWinPlaces() const;
    Positions getWallsPos() const;
    sf::Vector2i getPlayerPos() const;
    uint32_t getBoxesAmount() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};