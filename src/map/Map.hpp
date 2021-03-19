#pragma once
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>
#include "../LevelConfig.hpp"

class Map : public sf::Drawable, public sf::Transformable {
    sf::Texture m_tileAtlas;
    sf::VertexArray m_tiles;
public:
    sf::Texture& getTileAtlasTexture();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool createMap(const LevelConfig &levelConfig);
    
    Map(const LevelConfig& levelConfig);
    ~Map();

};