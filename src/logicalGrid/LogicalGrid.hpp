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
 * position, and WallCollision which looking for
 * walls on next move
 */

class LogicalGrid{
    protected:
        TileAtlas m_logicalGrid;
        int m_gridWidth;
        int m_gridHeight;
    public:

        LogicalGrid(const LevelConfig &lvlcfg) :
            m_gridWidth(0),
            m_gridHeight(0)
        {
            m_logicalGrid = lvlcfg.getTileAtlasLogicalGrid();
            //idk why it can`t divide it in init
            int tileSize = lvlcfg.getTileSize();
            m_gridWidth = WINDOW_WIDTH / tileSize;
            m_gridHeight = WINDOW_HEIGHT / tileSize;
        };

        virtual ~LogicalGrid() {};

        /*
         * This function convert index of one dimension table
         * to coordinates n grid
         */
        sf::Vector2i indexToPos(unsigned int index){
            int x = 0;
            int y = 0;

            for(int y = 0; y < m_gridHeight; y++)
                for(int x = 0; x < m_gridWidth; x++)
                    if(x + y * m_gridWidth == index)
                        return {x, y};
            return {-1, -1};
        }
};