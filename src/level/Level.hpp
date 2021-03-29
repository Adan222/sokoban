#pragma once

#include <string>
#include <stdexcept>
#include <functional>
#include <vector>

#include "entities/Entity.hpp"
#include "entities/physics/Physics.hpp"
#include "map/Map.hpp"
#include "LevelConfig.hpp"
#include "entities/Player.hpp"
#include "entities/Box.hpp"
#include "WinChecker.hpp"

constexpr unsigned short MAP_WITDH  = 16;
constexpr unsigned short MAP_HEIGHT = 12;

class Level {
     LevelConfig m_levelConfig;
    bool m_wantExit;

    Map lvlMap;

    Physics m_physics;
    WinChecker m_winChecker;
    Player m_player;
    Boxes m_boxes;

    void setEntitiesPosition();

    void handleMove(const sf::Keyboard::Key pressedKey);
    void playerMove(DIRECTION dir);

    /*
     * This function move selected box
     */
    void moveBox(DIRECTION dir);

    /*
     * This function
     */
    void disappoint();

    void iterate(std::function<void(int)> func);

public:
    Level(const std::string& filename);
    ~Level();

    void render(sf::RenderTarget& renderer);
    void update(const float deltaTime);
    void input(const sf::Keyboard::Key pressedKey);

    /*
     * Chek if want to exit this level
     * and go to the next
     */
    bool checkIfWantExit() const;
};