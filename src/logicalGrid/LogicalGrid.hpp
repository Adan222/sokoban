#pragma once

#include "level/LevelConfig.hpp"
#include <SFML/System/Vector2.hpp>
#include <sys/types.h>

enum LOGIC{
    FREE,
    WALL,
    PLAYER,
    BOX,
    WIN_PLACE,
    BOX_AND_WIN
};

/*
 * It`s abstract class for class like 
 * EntitiesPosition which looking for entiteis
 * position, and WallCollisions which looking for
 * walls on next move
 */

class LogicalGrid{
    protected:
        TileAtlas m_logicalGrid;
        int m_gridWidth;
        int m_gridHeight;
        
    public:

        LogicalGrid(const LevelConfig &lvlcfg);

        virtual ~LogicalGrid();

        /*
         * This function convert index of one dimension table
         * to coordinates on grid
         */
        sf::Vector2i indexToPos(u_int32_t index);

        /*
         * This function convert coordinates
         * to to index of logical grid
         */
        u_int32_t posToIndex(const sf::Vector2i pos);
};