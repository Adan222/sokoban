#pragma once

#include "level/LevelConfig.hpp"
#include "logicalGrid/LogicalGrid.hpp"
#include <SFML/System/Vector2.hpp>

class WallCollisions : public LogicalGrid
{
    public:
        WallCollisions(const LevelConfig &lvlcfg);
        ~WallCollisions();
        
        /*
         * Check on wall on given coords
         */
        bool check(const sf::Vector2i next);
};