#pragma once

#include <iostream>

#include "Entity.hpp"
#include "animation/AnimationHandler.hpp"
#include "guide/Guide.hpp"

typedef AnimationHandler PlayerAnimation;

class Player : public Entity
{
    sf::CircleShape m_PlayerShape;

    const float m_maxSpeed = 1;

    PlayerAnimation m_anime;

public:
    Player();
    ~Player();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    //void setTexture(sf::IntRect rec); 
    void setTexture(const sf::Color &col);
    void setAniamtion(DIRECTION type);

    void update(const float deltaTime) override;
};