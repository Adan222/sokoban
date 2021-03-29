#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <memory>

class wText : public sf::Text
{
    private:
        //maybe later
        //static std::shared_ptr<sf::Font> m_font;
        sf::Font m_font;
        
    public:
        wText() ;
        virtual ~wText();

        uint32_t getWidth() const;
        uint32_t getHeight() const;
};