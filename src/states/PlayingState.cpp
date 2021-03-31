#include "PlayingState.hpp"

namespace State {

PlayingState::PlayingState(Game& game, const int which) :
    State(game),
    m_whichLvl(which),
    m_isOnlyOne(false),
    m_scoreText(),
    m_score(0),
    m_isPopUpOnScreen(true),
    m_isWinNow(false),
    m_playerName("")
{
    m_level = std::make_unique<Level>(makePath(m_whichLvl));
    initText();
    createLeadBoardInputMenu();
}

PlayingState::PlayingState(Game& game, const std::filesystem::path path) :
    State(game),
    m_isOnlyOne(true),
    m_isPopUpOnScreen(false),
    m_isWinNow(false)
{
    m_level = std::make_unique<Level>(path);

    //We have to have one page
    //otherwise segmantation 
    createAfterWinPopUp();
}

PlayingState::~PlayingState() {}

void PlayingState::initText() {
    m_scoreText.setString("Score: 0\nMoves: 0");

    float x = 20;
    float y = WINDOW_HEIGHT - m_scoreText.getHeight() - 20;
    m_scoreText.setPosition({x, y});
}

void PlayingState::createAfterWinPopUp() {
    //Init page
    m_page.emplace_back(std::make_unique<WidgetStack>(m_game.getWindow()));

    m_page[getCurrentPage()]->setSize({250, 300});

    float x = (WINDOW_WIDTH - m_page[getCurrentPage()]->getSize().x) / 2;
    float y = (WINDOW_HEIGHT - m_page[getCurrentPage()]->getSize().y) / 2;
    m_page[getCurrentPage()]->setPosition({x, y});
    m_page[getCurrentPage()]->setBackgroundColor(sf::Color(150, 50, 250));


    //Init buttons
    auto nextBtn = std::make_unique<Button>(ButtonType::WIDE);
    auto exitBtn = std::make_unique<Button>(ButtonType::WIDE);

    sf::Vector2f rel = m_page[getCurrentPage()]->getPos();
    nextBtn->setRelative(rel);
    exitBtn->setRelative(rel);

    nextBtn->setString("Next");
    exitBtn->setString("Exit");

    //display on center
    float btn_x = (m_page[getCurrentPage()]->getSize().x - nextBtn->getWidth()) / 2;
    float btn_y_start = (m_page[getCurrentPage()]->getSize().y - 2 * nextBtn->getHeight()) / 2.5;

    //on the to of each other
    nextBtn->setPosition({btn_x, btn_y_start});
    exitBtn->setPosition({btn_x, btn_y_start + 1 * nextBtn->getHeight() + 1 * 10});

    nextBtn->setColor(sf::Color::Red);
    exitBtn->setColor(sf::Color::Blue);

    nextBtn->setFunction([this](){ 
        m_score += m_whichLvl;
        m_isPopUpOnScreen = false;
        m_isWinNow = false;
        if(m_whichLvl < 20){
            m_level.reset();
            m_level = std::make_unique<Level>(makePath(m_whichLvl++)); 
        }
        else
            wantExit();

    });
    exitBtn->setFunction([this](){ wantExit(); });

    m_page[getCurrentPage()]->addItem(std::move(nextBtn));
    m_page[getCurrentPage()]->addItem(std::move(exitBtn));
}

void PlayingState::createInGameMenu() {
    //Init page
    m_page.emplace_back(std::make_unique<WidgetStack>(m_game.getWindow()));

    m_page[getCurrentPage()]->setSize({250, 300});

    float x = (WINDOW_WIDTH - m_page[getCurrentPage()]->getSize().x) / 2;
    float y = (WINDOW_HEIGHT - m_page[getCurrentPage()]->getSize().y) / 2;
    m_page[getCurrentPage()]->setPosition({x, y});
    m_page[getCurrentPage()]->setBackgroundColor(sf::Color(150, 50, 250));


    //Init buttons
    auto saveGameBtn = std::make_unique<Button>(ButtonType::WIDE);
    auto exitBtn = std::make_unique<Button>(ButtonType::WIDE);

    sf::Vector2f rel = m_page[getCurrentPage()]->getPos();
    saveGameBtn->setRelative(rel);
    exitBtn->setRelative(rel);

    saveGameBtn->setString("Save Game");
    exitBtn->setString("Exit");

    //display on center
    float btn_x = (m_page[getCurrentPage()]->getSize().x - saveGameBtn->getWidth()) / 2;
    float btn_y_start = (m_page[getCurrentPage()]->getSize().y - 3 * saveGameBtn->getHeight()) / 2.5;

    //on the to of each other
    saveGameBtn->setPosition({btn_x, btn_y_start});
    exitBtn->setPosition({btn_x, btn_y_start + 1 * saveGameBtn->getHeight() + 1 * 10});

    saveGameBtn->setColor(sf::Color::Red);
    exitBtn->setColor(sf::Color::Blue);

    saveGameBtn->setFunction([this](){ m_level->savePlayerConfig(m_playerName, m_score); });
    exitBtn->setFunction([this](){ wantExit(); });

    m_page[getCurrentPage()]->addItem(std::move(saveGameBtn));
    m_page[getCurrentPage()]->addItem(std::move(exitBtn));
}



void PlayingState::createLeadBoardInputMenu() {
    //Init page
    m_page.emplace_back(std::make_unique<WidgetStack>(m_game.getWindow()));
    m_isWinNow = true;

    //m_page[getCurrentPage()]->clear();
    m_page[getCurrentPage()]->setSize({400, 250});

    float x = (WINDOW_WIDTH - m_page[getCurrentPage()]->getSize().x) / 2;
    float y = (WINDOW_HEIGHT - m_page[getCurrentPage()]->getSize().y) / 2;
    m_page[getCurrentPage()]->setPosition({x, y});
    m_page[getCurrentPage()]->setBackgroundColor(sf::Color(150, 50, 250));

    auto input = std::make_unique<TextBox>(m_playerName);
    auto saveBtn = std::make_unique<Button>(ButtonType::WIDE);

    //Init input
    input->setRelative(m_page[getCurrentPage()]->getPos());

    float inp_x = (m_page[getCurrentPage()]->getSize().x - input->getWidth()) / 2;
    float inp_y = 20;
    input->setPosition({inp_x, inp_y});

    //Init btn
    saveBtn->setRelative(m_page[getCurrentPage()]->getPos());
    saveBtn->setString("Save");
    saveBtn->setColor(sf::Color::Green);

    float btn_x = (m_page[getCurrentPage()]->getSize().x - saveBtn->getWidth()) / 2;
    float btn_y = m_page[getCurrentPage()]->getSize().y - saveBtn->getHeight() - 10;
    saveBtn->setPosition({btn_x, btn_y});

    saveBtn->setFunction([this](){
        m_isPopUpOnScreen = false;
        m_page[getCurrentPage()]->wantExit();
        std::cout << getCurrentPage() << "\n";
        m_isWinNow = false;
    });

    m_page[getCurrentPage()]->addItem(std::move(saveBtn));
    m_page[getCurrentPage()]->addItem(std::move(input));
}



uint32_t PlayingState::getCurrentPage() const {
    return m_page.size() - 1;
}

void PlayingState::draw(sf::RenderTarget& renderer) {
    m_level->render(renderer);

    if(!m_isOnlyOne){
        renderer.draw(m_scoreText);

        if(m_isPopUpOnScreen)
            renderer.draw(*m_page[getCurrentPage()]);
    }
}

void PlayingState::handleEvent(sf::Event e) {
    using Key = sf::Keyboard;

    switch (e.type) {
        case sf::Event::KeyPressed:{
            if(e.key.code == Key::Escape){
                if(m_isOnlyOne)
                    wantExit();
                else
                    if(!m_isWinNow){
                        if(m_isPopUpOnScreen){
                            if(m_page.empty())
                                m_isPopUpOnScreen = false;
                            else{
                                m_isPopUpOnScreen = false;
                                m_page.pop_back();
                            }
                        }
                        else{
                            createInGameMenu();
                            m_isPopUpOnScreen = true;
                        }
                            
                    }
            }
            //Other buttons
            else{
                if(!m_level->checkIfWantExit() && !m_isPopUpOnScreen)
                    m_level->input(e.key.code);

            }

        }break;

        default:{
            //if we have opened menu we handle it
            if(m_isPopUpOnScreen)
                m_page[getCurrentPage()]->handleEvent(e);
        }break;
    }

    if(!m_page.empty())
        if(m_page[getCurrentPage()]->checkIfWantExit())
            m_page.pop_back();
}

void PlayingState::update(const sf::Time deltaTime, bool fixed){
    m_level->update(deltaTime.asSeconds());

    //update displayed score and moves
    m_scoreText.setString(
        "Score: " + std::to_string(m_score) + "\n" + "Moves: "
        + std::to_string(m_level->getMoves())
    );

    //check for win 
    if(m_level->checkIfWantExit()){
        if(!m_isWinNow){

            // and do what yo have to do
            //that is
            switch (int(m_isOnlyOne)) {
                
                //exit 
                case true:
                    m_isWinNow = true;
                    m_level.reset();
                    wantExit();
                break;

                //or display win menu
                case false:
                    m_isPopUpOnScreen = true;
                    createAfterWinPopUp();
                    m_isWinNow = true;
                break;
            }
        }
    }

}

} // namespace State
