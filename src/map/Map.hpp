#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>
#include "level/LevelConfig.hpp"

class Map : public sf::Drawable, public sf::Transformable {
    sf::Texture m_tileAtlas;
    sf::VertexArray m_tiles;

    //It`s less confusion when level config is as class member
    const LevelConfig &m_levelConfig;
public:
    Map(const LevelConfig& levelConfig);
    ~Map();

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
    bool createMap();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture& getTileAtlasTexture();
};