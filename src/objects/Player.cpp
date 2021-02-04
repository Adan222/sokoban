#include "Player.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"


Player::Player() {

}

Player::Player(const float x, const float y, const float radius = 30.0f) : 
    m_PlayerShape(radius),
    m_radius(radius)
{
    m_PlayerShape.setFillColor(sf::Color::Yellow);
    m_PlayerShape.setPosition(x, y);
    //origin to center
    m_PlayerShape.setOrigin(m_radius, m_radius);
}


Player::~Player(){}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(m_PlayerShape);
}


void Player::move(const float x, const float y) {
    m_PlayerShape.move(x, y);
}


sf::Vector2f Player::getPos() const {
    return m_PlayerShape.getPosition();
}

void Player::setPosition(const float x, const float y) {
    m_PlayerShape.setPosition(x, y);
}

