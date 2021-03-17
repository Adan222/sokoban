#pragma once

#include <SFML/System/Vector2.hpp>

/*
 * Player will follow this object
 */

enum DIRECTION : int;

class Guide{
    private:
        sf::Vector2f m_pos;

        const float m_distance = 100.0f; 

    public:
        Guide(const sf::Vector2f pos);
        ~Guide();

        void move(DIRECTION d);
        sf::Vector2f getPosition() const;
};