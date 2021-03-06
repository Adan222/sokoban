#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

#include "map/Map.hpp"
#include "LevelConfig.hpp"

class Level {
    Map m_t1;
    LevelConfig m_levelConfig;
public:
    Level(const std::string& filename);
    void render(sf::RenderTarget& renderer);
    ~Level();
};