#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class FpsCounter : public sf::Drawable{
    private:
        sf::Font m_arial;
        sf::Text m_fpsText;

    public:
        FpsCounter(int windowWidth);
        ~FpsCounter();

        void draw(sf::RenderTarget& renderer, sf::RenderStates states) const override;
        void update(float deltaTime);
};