#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "../LevelConfig.hpp"

class Map : public sf::Drawable, public sf::Transformable {
    sf::Texture m_tileAtlas;
    sf::VertexArray m_tiles;
    
public:
    sf::Texture getTileAtlasTexture() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool createMap(const LevelConfig &levelConfig);
    
    Map();
    ~Map();

};