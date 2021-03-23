#include "Box.hpp"

Box::Box() :
    Entity(m_boxShape),
    m_boxShape({64, 64})
{
    m_boxShape.setFillColor(sf::Color::Red);
}

Box::~Box() {}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_boxShape);
}

void Box::imChosenOne() {
    std::cout << "juhu\n";
    m_isMoving = true;
}

void Box::imNotChosenOne() {
    m_isMoving = false;
}

void Box::pos() {
    std::cout << "x: " << m_boxShape.getPosition().x << "\n";
    std::cout << "y: " << m_boxShape.getPosition().y << "\n";
}
