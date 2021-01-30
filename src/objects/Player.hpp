#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

namespace Objects
{
    class Player : public Entity
    {
        sf::CircleShape m_PlayerShape;

        float m_radious;

    public:
        Player();
        Player(const float &x, const float &y, const float &radious);
        //idk czy to sie przyda
        //Player(const sf::Vector2u &vec);

        ~Player();

        sf::Vector2f getPos() const override;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void move(const float &x, const float &y) override;

        void setPosiotion(const float &x, const float &y);
    };

}