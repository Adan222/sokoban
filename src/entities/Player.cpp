#include "Player.hpp"
#include "entities/Entity.hpp"
#include <cmath>

Player::Player() :
    Entity(m_PlayerShape),
    m_PlayerShape(32.0f),
    m_anime(*this)
{
    m_PlayerShape.setFillColor(m_anime.starterAniamtion());
}

Player::~Player(){}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(m_PlayerShape);
}

void Player::setTexture(const sf::Color &col){
    m_PlayerShape.setFillColor(col);
}

void Player::setAniamtion(DIRECTION type) {
    m_anime.changeAniamtion(type);
}

void Player::update(const float deltaTime){

    if(m_isMoving){
        if(isWithGuide(m_currentDirection)){
            resetMoveVector();
            m_isMoving = false;
        }
        else{
            /*
             * Now move vector in not multiply by time
             * due to precision, and move by little value 
             * is smoth too
             */
            m_PlayerShape.move(m_moveVector);
            
            /*
             * But animation stil use time
             */
            m_anime.update(deltaTime);
        }
    }
}