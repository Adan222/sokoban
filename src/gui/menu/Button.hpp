#pragma once

#include "Widget.hpp"
#include "wText.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <iostream>
#include <string>

enum ButtonType{
    WIDE,
    CUBE
};

constexpr int STD_WIDE_BTN_WIDTH = 212;
constexpr int STD_WIDE_BTN_HEIGHT = 64;
constexpr int STD_CUBE_BTN_SIZE = 80;

class Button : public Widget
{
    private:
        wText m_text;
        sf::RectangleShape m_shape;
        ButtonType m_type;

        std::function<void(void)> m_func;

        //This function will execute in destructor
        std::function<void(void)> m_exitFunc;
        
        //It`s just center string in btn
        void update();

    public:
        //Create empty btn
        Button();

        //Create btn with predefined size
        Button(ButtonType type);
        ~Button();

        void draw(sf::RenderTarget& renderer, sf::RenderStates states) const override;
        void handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void setString(const std::string &str);
        void setPosition(const sf::Vector2f pos);
        void setFunction(std::function<void(void)> func);
        void setExitFunction(std::function<void(void)> func);
        void setColor(const sf::Color col);
        void setSize(const sf::Vector2f size);

        sf::Vector2f getPos() const override;

        uint32_t getWidth() const override;
        uint32_t getHeight() const override;
};