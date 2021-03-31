#include "Box.hpp"
#include "entities/Entity.hpp"
#include <SFML/Graphics/Rect.hpp>

Box::Box(const std::string &fileName) :
    Entity(m_boxShape),
    m_imChosen(false)
{
    std::string path = "../res/graphics/" + fileName;

    sf::IntRect boxPos = {4 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE};

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

void Box::pos() {
    std::cout << "x: " << m_boxShape.getPosition().x << "\n";
    std::cout << "y: " << m_boxShape.getPosition().y << "\n";
}
