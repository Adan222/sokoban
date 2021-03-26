#include "WidgetStack.hpp"
#include "gui/menu/Widget.hpp"

WidgetStack::WidgetStack(const sf::RenderWindow &window) :
    m_window(window)
{
    if(!m_backgroundTexture.loadFromFile("../res/graphics/game/dirt.png"))
        std::cout << "MainMenuState: Can`t load graphics\n";

    m_backgroundTexture.setRepeated(true);

    m_background.setTexture(m_backgroundTexture);
    m_background.setTextureRect({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
    //Make it darker
    m_background.setColor(sf::Color(255, 255, 255, 128));
}

WidgetStack::~WidgetStack() {}

void WidgetStack::draw(sf::RenderTarget& renderer, sf::RenderStates states) const {
    renderer.draw(m_background);

    int am = m_widgets.size();
    for(int i = 0; i < am; i++)
        renderer.draw(*m_widgets[i]);
}

void WidgetStack::handleEvent(sf::Event e) {
    int am = m_widgets.size();
    for(int i = 0; i < am; i++)
        m_widgets[i]->handleEvent(e, m_window);
}

void WidgetStack::addItem(std::unique_ptr<Widget> widget) {
    m_widgets.push_back(std::move(widget));
}


