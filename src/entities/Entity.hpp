#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

#include "guide/Guide.hpp"

#include <iostream>

constexpr unsigned short TILE_SIZE = 64;
constexpr unsigned short SPEED = 1;

enum DIRECTION : int{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NONE
};

//DRY

class Entity : public sf::Drawable{
    protected:
        sf::Shape &m_shape;

        bool m_isMoving;
        
        sf::Vector2f m_moveVector;

        sf::Vector2i m_gridPos;

        DIRECTION m_currentDirection;

        Guide m_guide;

        bool isWithGuide(DIRECTION dir) const;

        void resetMoveVector();

        //debug purpose
        void drawPos() const;

    
    public:
        Entity(sf::Shape &sh);
        virtual ~Entity();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

        void move(DIRECTION dir);
        
        sf::Vector2i getGridPos() const;

        virtual void update(const float deltaTime);

        void initPosition(const int grid_x, const int grid_y);
};
