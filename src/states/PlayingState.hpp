#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

#include "State.hpp"
#include "Game.hpp"
#include "gui/menu/Button.hpp"
#include "gui/menu/WidgetStack.hpp"
#include "gui/menu/wText.hpp"
#include "level/Level.hpp"
#include "sound/SoundManager.hpp"
#include "states/MainMenuState.hpp"
#include "gui/menu/TextBox.hpp"
#include "PlayerConfig.hpp"


namespace State {

class PlayingState : public State {
    std::unique_ptr<Level> m_level;
    PlayerConfig m_playerConfig;
    
    int m_whichLvl;

    /**
     * We have to specify if we play only one lvl or many
     * If we play one we exit to menu when you win
     */
    bool m_isOnlyOne;

    //Chcek if you win current level
    bool m_isWinNow;

    int m_score;
    std::string m_playerName;

    wText m_scoreText;

    /**
     * In game we will have only one pop up
     */ 
    bool m_isPopUpOnScreen;
    std::vector<std::unique_ptr<WidgetStack>> m_page;

    SoundManager m_sound;

    void initText();

    void createAfterWinPopUp();
    void createInGameMenu();
    void createLeadBoardInputMenu();

    uint32_t getCurrentPage() const;
    
public:
    /**
     * This constructor is used when we play until we 
     * want to exit.
     */
    PlayingState(Game& game, const int which);

    /**
     * This constructor is used when we play only once
     */
    PlayingState(Game& game, const std::string &path);
    
    ~PlayingState();
    
    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;

    void update(const sf::Time deltaTime, bool fixed = false) override;
};

}

