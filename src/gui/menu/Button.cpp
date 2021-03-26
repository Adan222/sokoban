#include "Button.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

Button::Button(ButtonType type) :
    m_text(),
    m_shape()
{
    switch (type) {
        case ButtonType::CUBE:
            m_shape.setSize({64, 64});
            break;
        case ButtonType::WIDE:
            m_shape.setSize({192, 64});
            break;
    }
    m_shape.setFillColor(sf::Color::Red);
}

Button::~Button() {}

void Button::draw(sf::RenderTarget& renderer, sf::RenderStates states) const {
    renderer.draw(m_shape);
    renderer.draw(m_text);
}

void Button::handleEvent(sf::Event e, const sf::RenderWindow &window) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(m_text.isPositionOnIt(sf::Mouse::getPosition(window)))
            m_func();
    }
}

void Button::setString(const std::string &str) {
    m_text.setString(str);
}

void Button::setPosition(const sf::Vector2f pos) {
    m_shape.setPosition(pos);
    sf::FloatRect sr = m_shape.getGlobalBounds();

    int pos_x = pos.x + (sr.width - m_text.getWidth()) / 2;
    int pos_y = pos.y + (sr.height - m_text.getHeight()) / 2.5;

    std::cout << m_shape.getSize().x << " " << m_shape.getSize().y << "\n";
    
    std::cout << pos_x << " " << pos_y << "\n";
    std::cout << "witdh: " << sr.width << "\n";
    std::cout << "height: " << sr.height << "\n";

    m_text.setPosition(pos_x, pos_y);
}

void Button::setFunction(std::function<void(void)> func) {
    m_func = func;
}

sf::Vector2f Button::getPos() const {
    return m_text.getPosition();
}





