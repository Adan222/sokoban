#pragma once

#include "gui/menu/Widget.hpp"
#include "gui/menu/wText.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class TextBox : public Widget
{
    private:
        std::string& m_text;
        wText m_label;
        wText m_textOnScreen;

        sf::RectangleShape m_frame;

        bool m_isFocus;

        void handleTextInput(sf::Event e);
        void handleClick(sf::Event e, const sf::RenderWindow &window);

        //Update string position
        void update();

        bool isValidCharacter(const uint8_t keyCode);
        bool isBackspace(const uint8_t keyCode);

    public:
        TextBox(std::string& m_text);
        ~TextBox();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void setPosition(const sf::Vector2f pos);

        sf::Vector2f getPos() const override;
        uint32_t getWidth() const override;
        uint32_t getHeight() const override;

        std::string getText() const;

};