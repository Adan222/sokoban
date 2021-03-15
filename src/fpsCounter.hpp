#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "config.hpp"

class fpsCounter : public sf::Drawable{
    private:
        sf::Font m_arial;
        sf::Text m_fpsText;

    public:
        fpsCounter(int windowWidth);
        ~fpsCounter();

        void draw(sf::RenderTarget& renderer, sf::RenderStates states) const override;
        void update(float deltaTime);
};