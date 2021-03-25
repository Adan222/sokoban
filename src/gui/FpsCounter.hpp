#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <string>

#include "menu/wText.hpp"

class FpsCounter : public wText
{
    public:
        FpsCounter(int windowWidth);
        ~FpsCounter();

        void update(const float deltaTime);
};