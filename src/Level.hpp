#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

#include "map/Map.hpp"
#include "LevelConfig.hpp"
#include "entities/Player.hpp"
#include "entities/Box.hpp"

constexpr unsigned int WINDOW_WIDTH = 1024;
constexpr unsigned int WINDOW_HEIGHT = 768;


class Level {
    Map m_t1;
    LevelConfig m_levelConfig;

    Player m_player;
    Box m_box;
public:
    Level(const std::string& filename);
    ~Level();

    void render(sf::RenderTarget& renderer);
    void update(const float deltaTime);
    void input(sf::Keyboard::Key k);
};