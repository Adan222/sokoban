#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <bits/stdint-uintn.h>

#include <iostream>

class wText : public sf::Text
{
    protected:
        sf::Font m_font;
        
    public:
        wText() ;
        virtual ~wText();

        uint32_t getWidth() const;
        uint32_t getHeight() const;
        
        bool isPositionOnIt(const sf::Vector2i pos) const;
};