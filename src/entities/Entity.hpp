#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "guide/Guide.hpp"

#include <iostream>

inline constexpr unsigned short TILE_SIZE = 64;
inline constexpr unsigned short SPEED = 1;

enum DIRECTION : int{
    LEFT,
    DOWN,
    RIGHT,
    UP,
    NONE
};

//DRY

class Entity : public sf::Drawable
{
    protected:
        sf::Transformable &m_transform;

        bool m_isMoving;
        
        sf::Vector2f m_moveVector;

        sf::Vector2i m_gridPos;

        DIRECTION m_currentDirection;

        Guide m_guide;

        bool isWithGuide(DIRECTION dir) const;

        void resetMoveVector();
    
    public:
        Entity(sf::Transformable &tr);
        virtual ~Entity();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

        void move(DIRECTION dir);
        
        sf::Vector2i getGridPos() const;

        virtual void update(const float deltaTime);

        void initPosition(const int grid_x, const int grid_y);

        bool isMoving() const;
};
