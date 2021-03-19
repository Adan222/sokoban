#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

#include "map/Map.hpp"
#include "LevelConfig.hpp"

class Level {
    //order here is important, we need to first initalize level config before passing it into Map constuctor
    LevelConfig m_levelConfig;
    Map m_t1;
public:
    Level(const std::string& filename);
    void render(sf::RenderTarget& renderer);
    ~Level();
};