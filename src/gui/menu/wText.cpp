#include "wText.hpp"

//std::shared_ptr<sf::Font> wText::m_font(nullptr);

wText::wText() 
{
    const std::string arialPath = "../res/fonts/Minecraft.ttf";
    if(!m_font.loadFromFile(arialPath))
        std::cout << "Can`t load font\n";


    setString("0");
    setFont(m_font);
    setFillColor(sf::Color::White);
}

wText::~wText() {}

uint32_t wText::getWidth() const{
    return getLocalBounds().width;
}

uint32_t wText::getHeight() const {
    return getLocalBounds().height;
}
