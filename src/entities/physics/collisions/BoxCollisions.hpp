#pragma once

#include "entities/Box.hpp"

#include <SFML/System/Vector2.hpp>

class BoxCollisions
{
    private:
        std::reference_wrapper<Boxes> m_boxes;
        int m_chosenOneIndex;

    public:
        BoxCollisions(Boxes &allBoxes);
        ~BoxCollisions();

        bool check(const sf::Vector2i nextPos);
        void action();
};