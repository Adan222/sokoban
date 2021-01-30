#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include <SFML/Graphics.hpp>

namespace Objects 
{
    class Entity : public sf::Drawable
    {
        public:
            Entity(){};
            virtual ~Entity() = default;

            virtual void move(const float &x, const float &y) = 0;

            virtual sf::Vector2f getPos() const = 0;

            //krawedzie
            /*
            virtual float up() const = 0;
            virtual float down() const = 0;
            virtual float right() const = 0;
            virtual float left() const = 0;
            */
    };

}