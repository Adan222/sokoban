#pragma once

#include <string>
#include <stdexcept>
#include <vector>

#include "entities/physics/Physics.hpp"
#include "map/Map.hpp"
#include "LevelConfig.hpp"
#include "entities/Player.hpp"
#include "entities/Box.hpp"

#include "EntitiesPosition.hpp"

constexpr unsigned short MAP_WITDH  = 16;
constexpr unsigned short MAP_HEIGHT = 12;

typedef void(function)(const int index);

class Level {
    const LevelConfig m_levelConfig;

    Physics m_physics;
    Player m_player;
    Boxes m_boxes;

    Map m_t1;
    int m_boxesAmount;

    void initMap();
    void setEntitisPosition();

    void handleMove(const sf::Keyboard::Key pressedKey);

    void moveBoxes(DIRECTION dir);
    void disappoint();

    void iterate(function func);

public:
    Level(const std::string& filename);
    ~Level();

    void render(sf::RenderTarget& renderer);
    void update(const float deltaTime);
    void input(const sf::Keyboard::Key pressedKey);
};