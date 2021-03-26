#pragma once

#include "Widget.hpp"
#include "wText.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <iostream>
#include <string>

enum ButtonType{
    WIDE,
    CUBE
};

class Button : public Widget
{
    private:
        wText m_text;
        sf::RectangleShape m_shape;
        ButtonType m_type;

        std::function<void(void)> m_func;

    public:
        Button(ButtonType type);
        ~Button();

        void draw(sf::RenderTarget& renderer, sf::RenderStates states) const override;
        void handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void setString(const std::string &str);
        void setPosition(const sf::Vector2f pos);
        void setFunction(std::function<void(void)> func);

        sf::Vector2f getPos() const override;
};