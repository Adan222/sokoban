#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "animation/PlayerAnimation.hpp"
#include "guide/PlayerGuide.hpp"

enum DIRECTION : int{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NONE
};

class Player : public sf::Drawable
{
    sf::CircleShape m_PlayerShape;
    float m_radius;

    const float m_maxSpeed = 100.0f;

    bool m_isMoving;

    DIRECTION m_currentDirection;

    //by default it`s {0, 0}
    sf::Vector2f m_moveVector;

    PlayerAnimation m_anime;
    Guide m_playerGuide;

    bool isPlayerWithGuide(DIRECTION d) const;
    void resetMoveVector();

    //debug purpose
    void drawPos() const;

public:
    Player(const int x, const int y);
    ~Player();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    //void setTexture(sf::IntRect rec); 
    void setTexture(const sf::Color &col);

    /*
     * This function is called when one of 
     * specific buttons was pressed.
     * It specify which and make specific behaviour.
     * General input is handle in PlayingState.
    */
    void handleInput(const sf::Keyboard::Key pressedKey);

    void update(float deltaTime);

};

