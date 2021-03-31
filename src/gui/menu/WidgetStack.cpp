#include "WidgetStack.hpp"


WidgetStack::WidgetStack(const sf::RenderWindow &window) :
    m_window(&window),
    m_backgroundTexture(),
    m_background({WINDOW_WIDTH, WINDOW_HEIGHT}),
    m_wantExit(false)
{}

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

void WidgetStack::eraseLastItem() {
    if(!m_widgets.empty())
        m_widgets.pop_back();
}

void WidgetStack::wantExit() {
    m_wantExit = true;
}

void WidgetStack::drawBackground() {

    if(!m_backgroundTexture.loadFromFile("../res/graphics/game/dirt.png"))
        std::cout << "MainMenuState: Can`t load graphics\n";

    m_backgroundTexture.setRepeated(true);

    //Make it darker
    m_background.setFillColor(sf::Color(255, 255, 255, 128));

    m_background.setSize({WINDOW_WIDTH, WINDOW_HEIGHT});
    m_background.setPosition({0, 0});
    m_background.setTexture(&m_backgroundTexture);
    m_background.setTextureRect({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
}

void WidgetStack::setSize(const sf::Vector2f size) {
    m_background.setSize(size);
}

void WidgetStack::setPosition(const sf::Vector2f pos) {
    m_background.setPosition(pos);
}

void WidgetStack::setBackgroundColor(const sf::Color col) {
    m_background.setFillColor(col);
}

void WidgetStack::clear() {
    m_widgets.clear();
}

bool WidgetStack::checkIfWantExit() const {
    return m_wantExit;
}

sf::Vector2f WidgetStack::getPos() const {
    return m_background.getPosition();
}

sf::Vector2f WidgetStack::getSize() const {
    return m_background.getSize();
}

const sf::RenderWindow& WidgetStack::getWindow() const{
    return *m_window;
}
