#pragma once

#include "Entity.hpp"

#include <iostream>

constexpr unsigned short MAX_BOXES = 12;

//Drawing on std::vector don`t work idk why
class Box;
typedef std::array<Box, MAX_BOXES> Boxes;

class Box : public Entity{
    private:
        sf::RectangleShape m_boxShape;
        bool m_imChosen;

    public:
        Box();
        ~Box();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void imChosenOne();
        void imNotChosenOne();
        bool chcekIfImChosen() const;

        void pos();
};