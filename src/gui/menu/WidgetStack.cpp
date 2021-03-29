#include "WidgetStack.hpp"


WidgetStack::WidgetStack(const sf::RenderWindow &window) :
    m_window(&window),
    m_backgroundTexture(),
    m_background()
{
    if(!m_backgroundTexture.loadFromFile("../res/graphics/game/dirt.png"))
        std::cout << "MainMenuState: Can`t load graphics\n";

    m_backgroundTexture.setRepeated(true);

    m_background.setTexture(m_backgroundTexture);
    m_background.setTextureRect({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
    //Make it darker
    m_background.setColor(sf::Color(255, 255, 255, 128));

}

WidgetStack::WidgetStack(WidgetStack &&other) : 
    m_window(&other.getWindow()),
    m_background(),
    m_backgroundTexture(),
    m_widgets(std::move(other.m_widgets))
{}

WidgetStack& WidgetStack::operator=(WidgetStack &&other) {
    m_window = &other.getWindow();
    m_background = other.m_background;
    m_backgroundTexture = other.m_backgroundTexture;
    m_widgets = std::move(other.m_widgets);

    return *this;
}

WidgetStack::~WidgetStack() {}

void WidgetStack::drawWidgets(sf::RenderTarget& renderer, sf::RenderStates states) const {
    int am = m_widgets.size();
    for(int i = 0; i < am; i++)
        renderer.draw(*m_widgets[i]);

}

void WidgetStack::draw(sf::RenderTarget& renderer, sf::RenderStates states) const {
    renderer.draw(m_background);
    drawWidgets(renderer, states);
}

void WidgetStack::handleEvent(sf::Event e) {
    int am = m_widgets.size();
    for(int i = 0; i < am; i++)
        m_widgets[i]->handleEvent(e, *m_window);
}

void WidgetStack::addItem(std::unique_ptr<Widget> widget) {
    m_widgets.emplace_back(std::move(widget));
}

int WidgetStack::size() const {
    return m_widgets.size();
}

const sf::RenderWindow& WidgetStack::getWindow() const{
    return *m_window;
}
