#include "Player.hpp"

Player::Player(const int x, const int y) : 
    m_PlayerShape(30.0f),
    m_radius(30.0f),
    m_anime(*this),
    m_playerGuide(sf::Vector2f(x, y)),
    m_isMoving(false),
    m_currentDirection(NONE)
{
    m_PlayerShape.setFillColor(m_anime.starterAniamtion());
    m_PlayerShape.setPosition(x, y);
    //origin to center
    m_PlayerShape.setOrigin(m_radius, m_radius);
}

Player::~Player(){}


bool Player::isPlayerWithGuide(DIRECTION d) const{

    const float pl_x = m_PlayerShape.getPosition().x;
    const float pl_y = m_PlayerShape.getPosition().y;

    const float gu_x = m_playerGuide.getPosition().x;
    const float gu_y = m_playerGuide.getPosition().y;

    switch (d){
        //I don`t know how it work lmao
        case UP:    return !(gu_y <= pl_y);
        case LEFT:  return !(gu_x <= pl_x);
        case DOWN:  return !(gu_y >= pl_y); 
        case RIGHT: return !(gu_x >= pl_x);
        case NONE:  return true;
    }
    return true;
}

void Player::resetMoveVector(){
    m_moveVector.x = 0;
    m_moveVector.y = 0;
}

void Player::drawPos() const{
    std::cout << "player x: " << m_PlayerShape.getPosition().x << "\n";
    std::cout << "player y: " << m_PlayerShape.getPosition().y << "\n";
    std::cout << "guide x: " << m_playerGuide.getPosition().x << "\n";
    std::cout << "guide y: " << m_playerGuide.getPosition().y << "\n";
}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(m_PlayerShape);
}


void Player::setTexture(const sf::Color &col){
    m_PlayerShape.setFillColor(col);
}


void Player::handleInput(const sf::Keyboard::Key pressedKey){
    handleMove(pressedKey);
}

void Player::handleMove(const sf::Keyboard::Key pressedKey){
    using Key = sf::Keyboard;

    //This block input when you`r moving 
    if(!m_isMoving){
        if(pressedKey == Key::W){
            m_currentDirection = UP;
            m_playerGuide.move(m_currentDirection);
            m_anime.changeAniamtion(m_currentDirection);
            m_moveVector.y = -m_maxSpeed;
        }

        if(pressedKey == Key::A){
            m_currentDirection = LEFT;
            m_playerGuide.move(m_currentDirection);
            m_anime.changeAniamtion(m_currentDirection);
            m_moveVector.x = -m_maxSpeed;
        }

        if(pressedKey == Key::S){
            m_currentDirection = DOWN;
            m_playerGuide.move(m_currentDirection);
            m_anime.changeAniamtion(m_currentDirection);
            m_moveVector.y = m_maxSpeed;
        }

        if(pressedKey == Key::D){
            m_currentDirection = RIGHT;
            m_playerGuide.move(m_currentDirection);
            m_anime.changeAniamtion(m_currentDirection);
            m_moveVector.x = m_maxSpeed;
        }
    }

    m_isMoving = true;
}

void Player::update(float deltaTime){

    if(m_isMoving){
        if(isPlayerWithGuide(m_currentDirection)){
            resetMoveVector();
            m_isMoving = false;
        }
        else{
            m_PlayerShape.move(m_moveVector * deltaTime);
            m_anime.update(deltaTime);
        }

        drawPos();
    }
}