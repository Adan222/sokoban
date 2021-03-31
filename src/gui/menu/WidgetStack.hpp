#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>

#include "Widget.hpp"

class WidgetStack : public sf::Drawable
{
    private:
        std::vector<std::unique_ptr<Widget>> m_widgets;

        const sf::RenderWindow *m_window;

        sf::RectangleShape m_background;
        sf::Texture m_backgroundTexture;

        void drawWidgets(sf::RenderTarget& renderer, sf::RenderStates states) const;

        bool m_wantExit;

    public:
        WidgetStack() = default;
        WidgetStack(const sf::RenderWindow &window);
        WidgetStack(WidgetStack &&other);
        WidgetStack& operator=(WidgetStack &&other);

        WidgetStack& operator=(const WidgetStack&) = delete;
        WidgetStack(const WidgetStack&) = delete;
            
        ~WidgetStack();

        void draw(sf::RenderTarget& renderer, sf::RenderStates states) const override;

        void handleEvent(sf::Event e);

        void addItem(std::unique_ptr<Widget> widget);
        void eraseLastItem();

        void wantExit();

        void drawBackground();
        void setSize(const sf::Vector2f size);
        void setPosition(const sf::Vector2f pos);
        void setBackgroundColor(const sf::Color col);

        void clear();

        bool checkIfWantExit() const;
        sf::Vector2f getPos() const;
        sf::Vector2f getSize() const;

        void impulse() const;

        const sf::RenderWindow& getWindow() const;
};