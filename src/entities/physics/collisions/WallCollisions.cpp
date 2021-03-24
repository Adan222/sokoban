#include "WallCollisions.hpp"

WallCollisions::WallCollisions(Positions &walls) :
    m_walls(walls)
{}

WallCollisions::~WallCollisions() {}

bool WallCollisions::check(const sf::Vector2i pos) {
    for(auto i : m_walls)
        if(i == pos)
            return true;
    return false;
}





