#include "entities/Player.hpp"

Guide::Guide(const sf::Vector2f pos) :
    m_pos(pos)
{}

Guide::~Guide() {}

void Guide::move(DIRECTION d){
    switch (d){
        case UP:
            m_pos.y -= m_distance; break;
        case LEFT:
            m_pos.x -= m_distance; break;
        case DOWN:
            m_pos.y += m_distance; break;
        case RIGHT:
            m_pos.x += m_distance; break;
        case NONE:
            /* Do nothing */ break;
    }
}

sf::Vector2f Guide::getPosition() const{
    return m_pos;
}