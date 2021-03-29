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
#include <vector>

#include "State.hpp"
#include "Game.hpp"
#include "PlayingState.hpp"
#include "gui/menu/Button.hpp"
#include "gui/menu/Title.hpp"
#include "gui/menu/WidgetStack.hpp"
#include "level/LevelConfig.hpp"


namespace State {

enum LevelOfDifficulty{
    EASY,
    MEDIUM,
    HARD
};

class MainMenuState : public State
{
    private:
        std::vector<WidgetStack> m_pages;

        /**
         * Source code of those functions
         * is in gui/menu/Page.cpp
         */
        void createMenuPage();
        void createModulesPage();
        void createOfficialLevelsPage();
        void createCustomLevels();

        void createErrorPopUp(const std::string &errorMsg);

        /**
         * We have to erase page at the end of frame.
         * Couse when we delate it immediately some func
         * will try to use delated page.
         * We delate it at the end of handeEvent()
         */
        bool m_pageWantExit;

        //Add or erase to pages stack
        void pushPage();
        void popPage();

        /**
         * This function return index of current page.
         * returning reference didn`t work
         */
        uint32_t getCurrentPage() const;


    public:
        MainMenuState(Game& game);
        ~MainMenuState();

    void update(const sf::Time deltaTime, bool fixed = false) override;
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
};


}