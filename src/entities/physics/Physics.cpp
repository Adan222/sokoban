#include "Physics.hpp"
#include "entities/Entity.hpp"
#include <SFML/System/Vector2.hpp>

Physics::Physics(const LevelConfig &lvlcfg, Boxes &allboxes) :
    m_boxCollisions(allboxes)
{}

Physics::~Physics() {}

void Physics::makeNext(sf::Vector2i &vec, DIRECTION d, const int i = 1){
    switch (d) {
        case UP: 
            vec.y -= i; break;

        case LEFT:
            vec.x -= i; break;

        case DOWN: 
            vec.y += i; break;

        case RIGHT:
            vec.x += i; break;

        case NONE: break;;
    }
}

bool Physics::checkBoxCollision(const sf::Vector2i currPos, DIRECTION dir){
    sf::Vector2i nextPos = currPos;

    makeNext(nextPos, dir);

    return m_boxCollisions.check(nextPos);
}

bool Physics::chcekNextObscatle(const sf::Vector2i currPos, DIRECTION dir){
    sf::Vector2i nextPos = currPos;

    //Pos behind box
    makeNext(nextPos, dir, 2);

    if(m_boxCollisions.check(nextPos)) // or wall - but it later
        return true;

    return false;
}

void Physics::action() {
    m_boxCollisions.action();
}

bool Physics::checkWall(const sf::Vector2i currPos, DIRECTION dir){
    return false;
}