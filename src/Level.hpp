#pragma once
#include <string>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

#include "map/Map.hpp"

class Level {
    using json = nlohmann::json;
    Map m_t1;
    json m_levelConfig;
    std::ifstream m_levelConfigStream;
public:
    Level(const std::string& filename);
    void render(sf::RenderTarget& renderer);
    ~Level();
};