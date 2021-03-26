#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <memory>
#include <chrono>

#include "State.hpp"
#include "Game.hpp"
#include "PlayingState.hpp"
#include "gui/menu/Button.hpp"
#include "gui/menu/Title.hpp"
#include "gui/menu/WidgetStack.hpp"
#include "level/LevelConfig.hpp"


namespace State {


class MainMenuState : public State{
    WidgetStack m_firstPage;

public:
    MainMenuState(Game& game);
    ~MainMenuState();

    void update(const float deltaTime) override;
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
};


}