#include "Box.hpp"

Box::Box() :
    Entity(m_boxShape),
    m_imChosen(false),
    m_boxTexture(),
    m_boxShape()
{
    sf::IntRect boxPos = {4 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE};

    std::string path = "../res/graphics/tile_new.png";
    if(!m_boxTexture.loadFromFile(path, boxPos))
        std::cout << "Can`t load box texutre\n";

    m_boxShape.setTexture(m_boxTexture);
}

Box::~Box() {}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_boxShape);
}

void Box::imChosenOne() {
    m_imChosen = true;
}

void Box::imNotChosenOne() {
    m_imChosen = false;
}

bool Box::checkIfImChosen() const {
    return m_imChosen;
}

