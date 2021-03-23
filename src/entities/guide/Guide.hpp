#pragma once

#include <SFML/System/Vector2.hpp>

/*
 * Entities will follow this object
 * Guide is working on grid positioning.
 * It mean that if you wan`t to have real position
 * you need to multiply position by TILE_SIZE
 */

enum DIRECTION : int;

class Guide{
    private:
        sf::Vector2i m_pos;

        const float m_distance = 1; 

    public:
        Guide();
        ~Guide();

        void init(const sf::Vector2i &in);
        void move(DIRECTION d);
        sf::Vector2i getPosition() const;
};