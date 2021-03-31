#pragma once

#include "level/LevelConfig.hpp"

#include <SFML/System/Vector2.hpp>

class WallCollisions
{
    private:
        //Walls don`t move
         Positions m_walls;

    public:
        WallCollisions(const Positions walls);
        ~WallCollisions();
        
        /*
         * Check on wall on given coords
         */
        bool check(const sf::Vector2i next);
};