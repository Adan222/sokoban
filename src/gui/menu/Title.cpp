#include "Title.hpp"
#include "gui/menu/Widget.hpp"
#include "level/LevelConfig.hpp"

Title::Title() :
    Widget(),
    m_text()
{
    m_text.setCharacterSize(100);
    m_text.setString("SOKOBAN");
    m_text.setLetterSpacing(2.5);
    uint32_t witdh = m_text.getWidth();

    uint32_t pos_x = (WINDOW_WIDTH - witdh) / 2;

    m_text.setPosition(pos_x, 48);
}

Title::~Title() {}

void Title::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(m_text);
}

sf::Vector2f Title::getPos() const{
    return m_text.getPosition();
}