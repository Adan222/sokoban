#pragma once

#include <SFML/Graphics.hpp>


class Player {
    sf::CircleShape m_PlayerShape;
    float m_radius;

public:
    Player();
    Player(const float x, const float y, const float radious);
    ~Player();

    sf::Vector2f getPos() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(const float x, const float y);
    void setPosition(const float x, const float y);
};

