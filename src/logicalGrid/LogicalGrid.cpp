#include "LogicalGrid.hpp"

LogicalGrid::LogicalGrid(const LevelConfig &lvlcfg) :
    m_gridWidth(0),
    m_gridHeight(0)
{
    m_logicalGrid = lvlcfg.getTileAtlasLogicalGrid();
    //idk why it can`t divide it in init
    int tileSize = lvlcfg.getTileSize();
    m_gridWidth = WINDOW_WIDTH / tileSize;
    m_gridHeight = WINDOW_HEIGHT / tileSize;
}

LogicalGrid::~LogicalGrid() {}

sf::Vector2i LogicalGrid::indexToPos(u_int32_t index){
    int x = 0;
    int y = 0;

    for(int y = 0; y < m_gridHeight; y++)
        for(int x = 0; x < m_gridWidth; x++)
            if(x + y * m_gridWidth == index)
                return {x, y};
    return {-1, -1};
}

uint32_t LogicalGrid::posToIndex(const sf::Vector2i pos) {
    int x = pos.x;
    int y = pos.y;
    return x + y * m_gridWidth;
}
