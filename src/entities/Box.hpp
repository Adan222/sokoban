#pragma once

#include <SFML/Graphics.hpp>

class Box : public sf::Drawable{
    private:
        sf::RectangleShape m_boxShape;
        const float m_boxSide = 100.0f;

    public:
        Box(const int x, const int y);
        ~Box();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};