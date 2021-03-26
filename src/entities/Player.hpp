#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

#include "Entity.hpp"
#include "animation/AnimationHandler.hpp"
#include "guide/Guide.hpp"

typedef AnimationHandler PlayerAnimation;

class Player : public Entity
{
    sf::Sprite m_playerSprite;
    sf::Texture m_playerTexture;

    PlayerAnimation m_anime;

public:
    Player();
    ~Player();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setTexture(const sf::IntRect &col);
    void setAniamtion(DIRECTION type);

    void update(const float deltaTime) override;
};