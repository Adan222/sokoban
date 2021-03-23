#include "WallCollisions.hpp"

WallCollisions::WallCollisions(const LevelConfig &lvlcfg) : 
    LogicalGrid(lvlcfg)
{}

WallCollisions::~WallCollisions() {}

bool WallCollisions::check(const sf::Vector2i pos) {
    u_int32_t index = posToIndex(pos);

    if(m_logicalGrid[index] == LOGIC::WALL)
        return true;
    //else
    return false;
}





