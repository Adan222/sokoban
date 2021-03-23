#include "entities/Player.hpp"

Guide::Guide() {}

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

void Guide::init(const sf::Vector2i &in){
    m_pos = in;
}

sf::Vector2i Guide::getPosition() const{
    return m_pos;
}