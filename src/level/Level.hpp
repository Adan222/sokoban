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
#include "sound/SoundManager.hpp"


class Level {
    LevelConfig m_levelConfig;
    std::reference_wrapper<SoundManager> m_soundManager;
    Map m_lvlMap;
    Physics m_physics;
    WinChecker m_winChecker;
    Player m_player;
    Boxes m_boxes;

    int m_moves;

    void setEntitiesPosition();

    void handleMove(const sf::Keyboard::Key pressedKey);
    void playerMove(DIRECTION dir);

    bool m_wantExit;
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
    Level(const std::string& filename, SoundManager &soundM);
    ~Level();

    void render(sf::RenderTarget& renderer);
    void update(const float deltaTime);
    void input(const sf::Keyboard::Key pressedKey);

    void savePlayerConfig(std::string &name, const int score);

    /*
     * Chek if want to exit this level
     * and go to the next
     */
    bool checkIfWantExit() const;

    int getMoves() const;
};