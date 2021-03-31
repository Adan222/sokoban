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
#include "PlayerConfig.hpp"


class Level {
    PlayerConfig* m_playerConfig;

    LevelConfig m_levelConfig;
    SoundManager m_soundManager;
    Map m_levelMap;
    Physics m_physics;
    WinChecker m_winChecker;
    Player m_player;
    Boxes m_boxes;

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
    Level(const std::string& filename);
    Level(PlayerConfig& playerConfig);
    ~Level();

    void render(sf::RenderTarget& renderer);
    void update(const float deltaTime);
    void input(const sf::Keyboard::Key pressedKey);
    void initSound();
    /*
     * Chek if want to exit this level
     * and go to the next
     */
    bool checkIfWantExit() const;
};