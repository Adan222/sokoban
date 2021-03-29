#pragma once

#include "gui/menu/Widget.hpp"
#include "gui/menu/wText.hpp"
#include <string>

class Title : public Widget
{
    private:
        wText m_text;
    public:
        Title(const std::string &str, const int size);
        Title();
        ~Title();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Vector2f getPos() const override;

        uint32_t getWidth() const override;
        uint32_t getHeight() const override;
};