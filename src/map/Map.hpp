#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include <SFML/Graphics.hpp>

class Map : public sf::Drawable, public sf::Transformable {
    using json = nlohmann::json;
    sf::Texture m_tileAtlas;
    sf::VertexArray m_tiles;
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Map();
    ~Map();
    bool createMap(const json &levelConfig);
};