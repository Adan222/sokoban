#include "Box.hpp"

Box::Box(const int x, const int y) :
    m_boxShape({100.0f, 100.0f})
{
    m_boxShape.setPosition(x, y);
    m_boxShape.setOrigin(m_boxSide / 2, m_boxSide / 2);
    m_boxShape.setFillColor(sf::Color::Red);
}

Box::~Box() {}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_boxShape);
}