#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>

#include "Widget.hpp"

/**
 * This is base class for Widgets 
 */
class WidgetStack : public sf::Drawable
{
    private:
        std::vector<std::unique_ptr<Widget>> m_widgets;

        const sf::RenderWindow *m_window;

        sf::Sprite m_background;
        sf::Texture m_backgroundTexture;

        void drawWidgets(sf::RenderTarget& renderer, sf::RenderStates states) const;

    public:
        WidgetStack() = default;
        WidgetStack(const sf::RenderWindow &window);
        WidgetStack(const WidgetStack &other) = delete;
        WidgetStack(WidgetStack &&other);
        WidgetStack& operator=(WidgetStack &&other);
        ~WidgetStack();

        void draw(sf::RenderTarget& renderer, sf::RenderStates states) const override;

        void handleEvent(sf::Event e);

        void addItem(std::unique_ptr<Widget> widget);

        int size() const;

        const sf::RenderWindow& getWindow() const;
};