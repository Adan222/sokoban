#include "Player.hpp"

Player::Player(const int x, const int y) : 
    m_PlayerShape(30.0f),
    m_radius(30.0f)
    #ifdef FIXED_TIME_TEST
    ,timer()
    #endif
{
    m_PlayerShape.setFillColor(sf::Color::Red);
    m_PlayerShape.setPosition(x, y);
    //origin to center
    m_PlayerShape.setOrigin(m_radius, m_radius);
}


Player::~Player(){}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(m_PlayerShape);
}


void Player::setTexture(const sf::Color &col){
    m_PlayerShape.setFillColor(col);
}


void Player::input(){
    using Key = sf::Keyboard;

    if(sf::Keyboard::isKeyPressed(Key::W))
        m_moveVector.y = -m_maxSpeed;
    
    else if(sf::Keyboard::isKeyPressed(Key::A))
        m_moveVector.x = -m_maxSpeed;
    
    else if(sf::Keyboard::isKeyPressed(Key::S))
        m_moveVector.y = m_maxSpeed;
    
    else if(sf::Keyboard::isKeyPressed(Key::D))
        m_moveVector.x = m_maxSpeed;  
    
    //if nothink is pressed - reset move vector
    else{
        m_moveVector.x = 0;
        m_moveVector.y = 0;
    }    
}

void Player::update(float deltaTime){

    //This make move only in one direction
    if(m_moveVector.x > 0 || m_moveVector.x < 0)
        m_moveVector.y = 0;
    else if(m_moveVector.y > 0 || m_moveVector.y < 0)
        m_moveVector.x = 0;

    m_PlayerShape.move(m_moveVector * deltaTime);
}
