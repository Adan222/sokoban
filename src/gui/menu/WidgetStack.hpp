#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>

#include "Widget.hpp"

class WidgetStack : public sf::Drawable
{
    private:
        std::vector<std::unique_ptr<Widget>> m_widgets;

        const sf::RenderWindow &m_window;

        sf::Sprite m_background;
        sf::Texture m_backgroundTexture;

    public:
        WidgetStack(const sf::RenderWindow &window);
        ~WidgetStack();

        void draw(sf::RenderTarget& renderer, sf::RenderStates states) const override;

        void handleEvent(sf::Event e);

        void addItem(std::unique_ptr<Widget> widget);
};