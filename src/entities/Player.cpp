#include "Player.hpp"

Player::Player() :
    Entity(m_playerSprite),
    m_anime(*this)
{
    if(!m_playerTexture.loadFromFile("../res/graphics/game/player_all.png"))
        std::cout << "Player: Can`t load from file\n";
    m_playerSprite.setTexture(m_playerTexture);
    m_playerSprite.setTextureRect(m_anime.starterAniamtion());
}

Player::~Player(){
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(m_playerSprite);
}

void Player::setTexture(const sf::IntRect &col){
    m_playerSprite.setTextureRect(col);
}

void Player::setAnimation(DIRECTION type) {
    m_anime.changeAnimation(type);
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
            m_playerSprite.move(m_moveVector);
            
            /*
             * But animation stil use time
             */
            m_anime.update(deltaTime);
        }
    }
}