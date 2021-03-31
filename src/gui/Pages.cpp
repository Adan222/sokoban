#include "level/LevelConfig.hpp"
#include "states/LevelEditorState.hpp"
#include "states/MainMenuState.hpp"
#include <SFML/Graphics/Color.hpp>
#include <filesystem>
#include <iterator>
#include <memory>
#include <string>

namespace State{

void MainMenuState::createMenuPage(){
    pushPage();
    setBackgound();
    std::cout << "page index: " << getCurrentPage() << "\n";

    
    //Create title in menu
    auto tit = std::make_unique<Title>();

    /**
     * Array of properties for buttons.
     * Couse we don`t want to make them all freehand,
     * We make them in loop with properties in all those arrays.
     * But this loop will make them in the center, if we want to make
     * button somewhere else, we have to make them independently
     */
    constexpr int btnAmmount = 4;
    const std::string btnStrings[btnAmmount] = {
        "Play",
        "Continue",
        "LeaderBoard",
        "Exit"
    };
    const std::function<void(void)> btnFunc[btnAmmount] = {
        [this](){     
            createModulesPage(); 
        },
        [this](){ createContinue(); },
        [this](){ createLeaderBoard(); },
        [this](){ m_game.exit(); }
    };

    for(int i = 0; i < btnAmmount; i++){
        auto btn = std::make_unique<Button>(ButtonType::WIDE);
        btn->setString(btnStrings[i]);
        btn->setFunction(btnFunc[i]);

        float x = tit->getPos().x + (float(tit->getWidth() - btn->getWidth()) / 2);
        float y = 300 + i * (btn->getHeight() + 30);
        btn->setPosition({x, y});

        m_pages[getCurrentPage()].addItem(std::move(btn));
    }
    m_pages[getCurrentPage()].addItem(std::move(tit));
}



void MainMenuState::createModulesPage(){
    pushPage();
    setBackgound();
    std::cout << "create Modules Page\n";
    std::cout << "page index: " << getCurrentPage() << "\n";

    auto tit = std::make_unique<Title>();

    /**
     * Arrays of properties for buttons.
     * Couse we don`t want to make them all freehand,
     * We make them in loop with properties bellow.
     * But this loop will make them in the center, if we want to make
     * button somewhere else, we have to make them independently
     */
    constexpr int btnAmmount = 5;
    const std::array<std::string, btnAmmount> btnStrings = {
        "Easy",
        "Medium",
        "Hard",
        "All lvls",
        "Editor"
    };
    const std::array<std::function<void(void)>, btnAmmount> btnFunc = {
        [this](){ playOnce(LevelDifficult::EASY); },
        [this](){ playOnce(LevelDifficult::NORMAL); },
        [this](){ playOnce(LevelDifficult::HARD); },
        [this](){ createAllLevelsPage(); },
        [this](){ m_game.pushState(std::make_unique<LevelEditorState>(m_game)); }
    };
    const std::array<sf::Color, btnAmmount> btnColor = {
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Red,
        sf::Color::Magenta,
        sf::Color::Cyan
    };

    for(int i = 0; i < btnAmmount; i++){
        auto btn = std::make_unique<Button>(ButtonType::WIDE);
        btn->setString(btnStrings[i]);
        btn->setFunction(btnFunc[i]);

        float x = tit->getPos().x + (float(tit->getWidth() - btn->getWidth()) / 2);
        float y = 250 + i * (btn->getHeight() + 30);
        btn->setPosition({x, y});

        if(i < btnColor.size())
            btn->setColor(btnColor[i]);

        m_pages[getCurrentPage()].addItem(std::move(btn));
    }
    m_pages[getCurrentPage()].addItem(std::move(tit));

    createBackBtn();
}



void MainMenuState::createAllLevelsPage(){
    pushPage();
    setBackgound();
    std::cout << "create Official Levels Page\n";
    std::cout << "page index: " << getCurrentPage() << "\n";

    auto tit = std::make_unique<Title>("Levels", 64);

    //just for count start x
    auto test = std::make_unique<Button>(ButtonType::CUBE);

    //x axis start with padding
    const int cols = 5;
    const int padding_x_amount = cols + 1;
    const float padding_x = float(WINDOW_WIDTH - cols * test->getWidth()) / padding_x_amount;

    const int row = 4;
    const float start_y = tit->getPos().y + tit->getHeight() + 60;

    const int padding_y_amount = cols;
    const float padding_y = (WINDOW_HEIGHT - start_y - row * test->getHeight()) / padding_y_amount;

    float last_x = 0;
    float last_y = 0;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < cols; j++){ 
            const int index = j + i * cols;
            auto btn = std::make_unique<Button>(ButtonType::CUBE);
            btn->setString(std::to_string(index + 1));
            
            //set positions
            float x = 0;
            float y = start_y + i * (btn->getHeight() + padding_y);

            if(j == 0)
                x = padding_x;
            else
                x = last_x + btn->getWidth() + padding_x;

            last_x = x;
            btn->setPosition({x, y});

            
            //set colors
            btn->setColor(sf::Color::Green);
            if(index >= NORMAL_LVL)
                btn->setColor(sf::Color::Blue);
            if(index >= EASY_LVL + NORMAL_LVL)
                btn->setColor(sf::Color::Red);

            btn->setFunction([this, index](){
                //you can play if there is no error
                if(!m_isError)
                    playUntilExit(index); 
            });

            m_pages[getCurrentPage()].addItem(std::move(btn));
        }
        last_x = 0;
    }

    createBackBtn();
    m_pages[getCurrentPage()].addItem(std::move(tit));

    validateAll();
}

void MainMenuState::createErrorPopUp(const std::string &errorMsg, const bool makePerm)
{
    auto errBtn = std::make_unique<Button>(ButtonType::WIDE);
    errBtn->setString(errorMsg);
    errBtn->setColor(sf::Color::Red);

    float x = float(WINDOW_WIDTH - errBtn->getWidth()) / 2;
    float y = 150;
    errBtn->setPosition({x, y});

    /**
     * We assume that error btn is last element of the
     * current WidgetStack
     */
    errBtn->setFunction([this](){
        m_pages[getCurrentPage()].eraseLastItem();
    });
    if(makePerm){
        errBtn->setExitFunction([this](){
            m_isError = false;
        });
    }

    m_pages[getCurrentPage()].addItem(std::move(errBtn));
    m_isError = true;
}

void MainMenuState::createBackBtn(){
    auto backBtn = std::make_unique<Button>(ButtonType::WIDE);
    backBtn->setString("<-");
    backBtn->setColor(sf::Color::Transparent);
    backBtn->setPosition({10, 10});

    backBtn->setFunction([this](){
        m_pageWantExit = true;
    });

    m_pages[getCurrentPage()].addItem(std::move(backBtn));
}

void MainMenuState::createLeaderBoard(){
    pushPage();
    setBackgound();
    std::cout << "createLeaderBoard Page\n";
    std::cout << "page index: " << getCurrentPage() << "\n";

    auto tit = std::make_unique<Title>("Leader Board", 64);

    auto menu =  std::make_unique<Button>();
    menu->setString("NAME:\t\t\t\t\tScore:");

    float x = float(WINDOW_WIDTH - menu->getWidth()) / 2;
    float y = 150;
    menu->setPosition({x, y});
    menu->setColor(sf::Color::Transparent);
    m_pages[getCurrentPage()].addItem(std::move(menu));

    int i = 0;
    for(auto fileName : std::filesystem::directory_iterator("../res/saves")){
        auto player =  std::make_unique<Button>();

        /**
         * Here try to open fileName
         * and assign player name and score to dispText
         */

        std::string dispText = "Adam Małysz\t\t1234";
        player->setString(dispText);

        float x = float(WINDOW_WIDTH - player->getWidth()) / 2;
        float y = 200 + i * player->getHeight() + i * 50;
        player->setPosition({x, y});
        player->setColor(sf::Color::Transparent);

        m_pages[getCurrentPage()].addItem(std::move(player));
        i++;
    }
    if(i == 0){
        auto empty = std::make_unique<Button>();

        empty->setString("Empty");

        float x = float(WINDOW_WIDTH - empty->getWidth()) / 2;
        float y = 300;
        empty->setPosition({x, y});
        empty->setColor(sf::Color::Transparent);
        m_pages[getCurrentPage()].addItem(std::move(empty));
    }

    createBackBtn();

    m_pages[getCurrentPage()].addItem(std::move(tit));
}

void MainMenuState::createContinue(){
    pushPage();
    setBackgound();
    std::cout << "createContinue Page\n";
    std::cout << "page index: " << getCurrentPage() << "\n";

    auto tit = std::make_unique<Title>("Saves", 64);

    //just for count start x
    auto test = std::make_unique<Button>(ButtonType::CUBE);

    //x axis start with padding
    const int cols = 5;
    const int padding_x_amount = cols + 1;
    const float padding_x = float(WINDOW_WIDTH - cols * test->getWidth()) / padding_x_amount;

    const int row = 4;
    const float start_y = tit->getPos().y + tit->getHeight() + 60;

    const int padding_y_amount = cols;
    const float padding_y = (WINDOW_HEIGHT - start_y - row * test->getHeight()) / padding_y_amount;

    float last_x = 0;
    float last_y = 0;

    
    auto iterator = std::filesystem::directory_iterator("../res/saves");
    for(int i = 0; i < row; i++){
        for(int j = 0; j < cols; j++){ 
            

            if(iterator != std::filesystem::directory_iterator()){
                const int index = j + i * cols;
                std::cout << index << "\n";
                auto btn = std::make_unique<Button>(ButtonType::CUBE);
                btn->setString(iterator->path().stem().generic_string());
                
                //set positions
                float x = 0;
                float y = start_y + i * (btn->getHeight() + padding_y);

                if(j == 0)
                    x = padding_x;
                else
                    x = last_x + btn->getWidth() + padding_x;

                last_x = x;
                btn->setPosition({x, y});
                btn->setColor(sf::Color::Green);
                btn->setFunction([this, iterator](){ 
                    //here you call your constructor
                    playFromSave(iterator->path());
                });

                iterator++;
                 m_pages[getCurrentPage()].addItem(std::move(btn));
            }


           
        }
        last_x = 0;
    }

    createBackBtn();
    m_pages[getCurrentPage()].addItem(std::move(tit));
}

} //namespace
