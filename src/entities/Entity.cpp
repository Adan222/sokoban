#include "Entity.hpp"

Entity::Entity(sf::Transformable &tr) :
    m_transform(tr),
    m_isMoving(false),
    m_guide(),
    m_currentDirection(NONE)
{}

Entity::~Entity() {};

void Entity::move(DIRECTION dir) {
    
    switch (dir){
        case UP:{
            m_currentDirection = UP;

            m_moveVector.y = -SPEED;
            m_gridPos.y -= 1; 
        }break;

        case LEFT:{
            m_currentDirection = LEFT;

           m_moveVector.x = -SPEED;
            m_gridPos.x -= 1;
        }break;

        case DOWN: {
            m_currentDirection = DOWN;

            m_moveVector.y = SPEED;
            m_gridPos.y += 1;
        }break;

        case RIGHT:{
            m_currentDirection = RIGHT;

            m_moveVector.x = SPEED;
            m_gridPos.x += 1;
        }break;

        case NONE:{}break; 
    } //switch

    m_guide.move(m_currentDirection);

    m_isMoving = true;
}

sf::Vector2i Entity::getGridPos() const{
    return m_gridPos;
}

void Entity::update(const float deltaTime) {
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
            m_transform.move(m_moveVector);
        }
    }
}

void Entity::initPosition(const int grid_x, const int grid_y) {
    m_guide.init({grid_x, grid_y});
    m_gridPos = {grid_x, grid_y};
    m_transform.setPosition(grid_x * TILE_SIZE, grid_y * TILE_SIZE);

    drawGridPos();
}

bool Entity::isMoving() const {
    return m_isMoving;
}

bool Entity::isWithGuide(DIRECTION dir) const {
    const float ent_x = m_transform.getPosition().x;
    const float ent_y = m_transform.getPosition().y;

    const float gu_x = m_guide.getPosition().x * TILE_SIZE;
    const float gu_y = m_guide.getPosition().y * TILE_SIZE;

    switch (dir){
        case UP:    return (gu_y >= ent_y);
        case LEFT:  return (gu_x >= ent_x);
        case DOWN:  return (gu_y <= ent_y); 
        case RIGHT: return (gu_x <= ent_x);
        case NONE:  return false;
    }
    return false;
}

void Entity::resetMoveVector(){
    m_moveVector.x = 0;
    m_moveVector.y = 0;
}

void Entity::drawPos() const {
    std::cout << "ent x: " << m_transform.getPosition().x << "\n";
    std::cout << "ent y: " << m_transform.getPosition().y << "\n";
    std::cout << "guide x: " << m_guide.getPosition().x * TILE_SIZE << "\n";
    std::cout << "guide y: " << m_guide.getPosition().y * TILE_SIZE << "\n\n";
}

void Entity::drawGridPos() const {
    std::cout << "Grid pos\n";
    std::cout << "x: " << m_gridPos.x << "\n";
    std::cout << "y: " << m_gridPos.y << "\n\n";
}



