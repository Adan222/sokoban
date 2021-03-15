#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "animation/PlayerAnimation.hpp"


class Player : public sf::Drawable
{
    sf::CircleShape m_PlayerShape;
    float m_radius;

    const float m_maxSpeed = 100.0f;

    //by default it`s {0, 0}
    sf::Vector2f m_moveVector;

    PlayerAnimation m_anime;

public:
    Player(const int x, const int y);
    ~Player();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    //void setTexture(sf::IntRect rec); 
    void setTexture(const sf::Color &col);

    void input();
    void update(float deltaTime);

};

