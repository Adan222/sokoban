#pragma once

#include "level/LevelConfig.hpp"
#include "map/Map.hpp"

#include <SFML/System/Vector2.hpp>
#include <sys/types.h>

/*
 * It`s abstract class for class like 
 * EntitiesPosition which looking for entiteis
 * position, and WallCollisions which looking for
 * walls on next move
 */

class LogicalGrid {
    protected:
        Grid m_logicalGrid;
        int m_gridWidth;
        int m_gridHeight;
        
    public:

        LogicalGrid(const LevelConfig &lvlcfg);

        virtual ~LogicalGrid();

        /*
         * This function convert index of one dimension table
         * to coordinates on grid
         */
        sf::Vector2i indexToPos(uint32_t index);

        /*
         * This function convert coordinates
         * to to index of logical grid
         */
        uint32_t posToIndex(const sf::Vector2i pos);
};