#include "wText.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

wText::wText() :
    m_font()
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


bool wText::isPositionOnIt(const sf::Vector2i pos) const{
    sf::FloatRect rect = getGlobalBounds();
    sf::Vector2f f = {static_cast<float>(pos.x), static_cast<float>(pos.y)};
    return rect.contains(f);
}
