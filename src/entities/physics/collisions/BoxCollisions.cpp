#include "BoxCollisions.hpp"

BoxCollisions::BoxCollisions(Boxes &allBoxes) :
    m_boxes(allBoxes),
    m_chosenOneIndex(-1)
{}

BoxCollisions::~BoxCollisions() {}

bool BoxCollisions::check(const sf::Vector2i nextPos){

    for(int i = 0; i < m_boxes.size(); i++)
        if(m_boxes[i].getGridPos() == nextPos){
            m_chosenOneIndex = i;
            return true;
        }

    //else
    return false;
}

void BoxCollisions::action() {
    if(m_chosenOneIndex > 0)
        m_boxes[m_chosenOneIndex].imChosenOne();
}

