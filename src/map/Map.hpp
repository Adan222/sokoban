#pragma once
#include <iostream>
#include <string>
#include <../vendor/nlohmann/include/json.hpp>

#include <SFML/Graphics.hpp>


class Map {
    using json = nlohmann::json;
    sf::Texture m_tileAtlas;
    sf::VertexArray m_tiles;
public:
    Map();
    ~Map();
    bool createMap(const json &levelConfig);
};