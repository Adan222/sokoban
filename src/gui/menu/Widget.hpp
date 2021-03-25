#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "level/LevelConfig.hpp"

class Widget : public sf::Drawable
{
    public:
        Widget() {}
        virtual ~Widget() {}

        void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window) {}

        virtual sf::Vector2f getPos() const = 0;
};