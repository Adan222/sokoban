#include "MainMenuState.hpp"
#include "gui/menu/Button.hpp"
#include "level/LevelConfig.hpp"
#include "states/PlayingState.hpp"
#include <SFML/Graphics/Color.hpp>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <memory>
#include <string>

namespace State {


MainMenuState::MainMenuState(Game &game) :
    State(game),
    m_pageWantExit(false),
    m_isError(false)
{
    /**
     * We have to reserve elemnts in vector
     * couse we can`t copy WidgetStack
     */
    m_pages.reserve(10);

    //createModulesPage();
    createMenuPage();
}

MainMenuState::~MainMenuState() {}

int MainMenuState::randomNumber(const int start, const int numbers) {
    srand(time(NULL));

    return (rand() % numbers) + start;
}


uint32_t MainMenuState::getCurrentPage() const {
    return m_pages.size()-1;
}

void MainMenuState::playOnce(LevelDifficult diff) {
    int lvlIndex = 1;
    switch (diff) {
        case LevelDifficult::EASY:
            lvlIndex = randomNumber(1 , 6); break;
        case LevelDifficult::NORMAL:
            lvlIndex = randomNumber(7 , 7); break;
        case LevelDifficult::HARD:
            lvlIndex = randomNumber(14 , 6); break;
    }
    std::filesystem::path path = makePath(lvlIndex);


    if(LevelConfig::validateJSON(path))
        m_game.pushState(std::make_unique<PlayingState>(m_game, path));
    else
        if(!m_isError)
            createErrorPopUp("Level validation failed");
}

void MainMenuState::playUntilExit(const int whichLvl) {
    m_game.pushState(std::make_unique<PlayingState>(m_game, whichLvl+1));
}

void MainMenuState::playFromSave(std::filesystem::path savePath) {
    PlayerConfig playerConfig(savePath);
    m_game.pushState(std::make_unique<PlayingState>(m_game, playerConfig));
}

void MainMenuState::validateAll() {
    for(int i = 0; i < MAX_OFFICIAL_LVL; i++){
        std::filesystem::path path = makePath(i+1);

        if(!LevelConfig::validateJSON(path)){
            if(!m_isError){
                std::string errMsg = 
                    std::to_string(i) + " level validation failed\n";
                createErrorPopUp(errMsg, false);
                break;
            }
        }
    }
}

void MainMenuState::pushPage() {
    m_pages.emplace_back(WidgetStack(m_game.getWindow()));
}

void MainMenuState::popPage() {
    if(!m_pages.empty())
        m_pages.pop_back();
}

void MainMenuState::draw(sf::RenderTarget &renderer) {
    if(!m_pageWantExit)
        renderer.draw(m_pages[getCurrentPage()]);
}

void MainMenuState::update(const sf::Time deltaTime, bool fixed ) {

}

void MainMenuState::handleEvent(sf::Event e) {
    if(e.type == sf::Event::KeyPressed){
        switch (e.key.code) {
            case sf::Keyboard::Escape:
                m_game.exit();
                break;
            default:
                break;
        }   
    }
    if(e.type == sf::Event::MouseButtonPressed){
        m_pages[getCurrentPage()].handleEvent(e);
    }

    if(m_pageWantExit){
        popPage();
        m_pageWantExit = false;
    }
}

}   //namespace State