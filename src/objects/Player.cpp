#include "Player.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "objects/Entity.hpp"

namespace Objects 
{

/*idk czy to sie przyda
    Player::Player(const sf::Vector2u &vec) : 
    m_playerPos(vec),
    m_PlayerShape(30.0f),
    velocity(30.0f)
{
    m_PlayerShape.setFillColor(sf::Color::Yellow);
}
*/


Player::Player(const float &x, const float &y, const float &radious) : 
    m_PlayerShape(radious),
    m_radious(radious)
{
    m_PlayerShape.setFillColor(sf::Color::Yellow);
    m_PlayerShape.setPosition(x, y);
    //origin to center
    m_PlayerShape.setOrigin(m_radious, m_radious);
}


Player::~Player(){}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_PlayerShape);
}


void Player::move(const float &x, const float &y)
{
    m_PlayerShape.move(x, y);
}


sf::Vector2f Player::getPos() const
{
    return m_PlayerShape.getPosition();
}

}   //namespace Objects
