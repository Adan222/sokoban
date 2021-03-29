#include "Button.hpp"
#include <SFML/System/Vector2.hpp>

Button::Button() :
    m_text(),
    m_shape(),
    m_func([](){})
{}

Button::Button(ButtonType type) :
    m_text(),
    m_shape(),
    m_func([](){})
{
    switch (type) {
        case ButtonType::CUBE:
            m_shape.setSize({STD_CUBE_BTN_SIZE, STD_CUBE_BTN_SIZE});
            break;
        case ButtonType::WIDE:
            m_shape.setSize({STD_WIDE_BTN_WIDTH, STD_WIDE_BTN_HEIGHT});
            break;
    }
    m_shape.setFillColor(sf::Color::Red);
}

Button::~Button() {}

void Button::update() {
    const sf::Vector2f pos = m_shape.getPosition();
    const sf::FloatRect sr = m_shape.getGlobalBounds();

    int pos_x = pos.x + (sr.width - m_text.getWidth()) / 2;
    int pos_y = pos.y + (sr.height - m_text.getHeight()) / 2.5;
    
    m_text.setPosition(pos_x, pos_y);
}

void Button::draw(sf::RenderTarget& renderer, sf::RenderStates states) const {
    renderer.draw(m_shape);
    renderer.draw(m_text);
}

void Button::handleEvent(sf::Event e, const sf::RenderWindow &window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        if(m_shape.getGlobalBounds().contains(mousePos))
            m_func();
}

void Button::setString(const std::string &str) {
    m_text.setString(str);
    update();
}

void Button::setPosition(const sf::Vector2f pos) {
    m_shape.setPosition(pos);
    update();
}

void Button::setFunction(std::function<void(void)> func) {
    m_func = func;
}

void Button::setColor(const sf::Color col) {
    m_shape .setFillColor(col);
}

void Button::setSize(const sf::Vector2f size) {
    m_shape.setSize(size);
    update();
}

sf::Vector2f Button::getPos() const {
    return m_text.getPosition();
}

uint32_t Button::getWidth() const{
    return m_shape.getGlobalBounds().width;
}

uint32_t Button::getHeight() const{
    return  m_shape.getGlobalBounds().height;
}