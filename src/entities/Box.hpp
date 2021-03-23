#pragma once

#include "Entity.hpp"

#include <iostream>

constexpr unsigned short MAX_BOXES = 12;

class Box;
typedef std::array<Box, MAX_BOXES> Boxes;

class Box : public Entity{
    private:
        sf::RectangleShape m_boxShape;

    public:
        Box();
        ~Box();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void imChosenOne();
        void imNotChosenOne();

        void pos();
};