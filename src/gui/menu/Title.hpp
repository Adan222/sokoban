#pragma once

#include "gui/menu/Widget.hpp"
#include "gui/menu/wText.hpp"

class Title : public Widget
{
    private:
        wText m_text;
    public:
        Title();
        ~Title();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Vector2f getPos() const override;
};