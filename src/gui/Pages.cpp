#include "gui/menu/WidgetStack.hpp"
#include "states/MainMenuState.hpp"
#include <SFML/Graphics/Color.hpp>
#include <array>

namespace State{

void MainMenuState::createMenuPage(){
    pushPage();
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
    constexpr int btnAmmount = 3;
    const std::string btnStrings[btnAmmount] = {
        "Graj",
        "LeadeBoard",
        "Exit"
    };
    const std::function<void(void)> btnFunc[btnAmmount] = {
        [this](){     
            createModulesPage(); 
        },

        [this](){ std::cout << "LeadeBoard\n"; },
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
        [this](){ std::cout << "Easy\n"; },
        [this](){ std::cout << "Medium\n"; },
        [this](){ std::cout << "Hard\n"; },
        [this](){ createOfficialLevelsPage(); },
        [this](){ std::cout << "Editor\n"; }
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

    //Back button
    auto backBtn = std::make_unique<Button>(ButtonType::WIDE);
    backBtn->setString("<-");
    backBtn->setColor(sf::Color::Transparent);
    backBtn->setPosition({10, 10});

    backBtn->setFunction([this](){
        m_pageWantExit = true;
    });

    m_pages[getCurrentPage()].addItem(std::move(backBtn));
}

void MainMenuState::createOfficialLevelsPage(){
    pushPage();
    std::cout << "create Official Levels Page\n";
    std::cout << "page index: " << getCurrentPage() << "\n";

    auto tit = std::make_unique<Title>("Levels", 64);

    //just for count start x
    auto test = std::make_unique<Button>(ButtonType::CUBE);

    //x axis start with padding
    const int padding_x_amount = 7;
    const float padding_x = float(WINDOW_WIDTH - 6 * test->getWidth()) / padding_x_amount;

    const float start_y = tit->getPos().y + tit->getHeight() + 60;
    const int padding_y_amount = 5;
    const float padding_y = (WINDOW_HEIGHT - start_y - 5 * test->getHeight()) / padding_y_amount;

    float last_x = 0;
    float last_y = 0;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){ 
            const int index = j + i * 6;
            auto btn = std::make_unique<Button>(ButtonType::CUBE);
            btn->setString(std::to_string(index + 1));
            
            float x = 0;
            float y = start_y + i * (btn->getHeight() + padding_y);

            if(j == 0)
                x = padding_x;
            else
                x = last_x + btn->getWidth() + padding_x;

            last_x = x;
            
            btn->setColor(sf::Color::Green);
            if(index >= 10)
                btn->setColor(sf::Color::Blue);
            if(index >= 20)
                btn->setColor(sf::Color::Red);

            //const std::string pathToLevel = "../res/levels/official/level" + std::to_string(index);

            btn->setFunction([this](){ createOfficialLevelsPage(); });

            btn->setPosition({x, y});
            m_pages[getCurrentPage()].addItem(std::move(btn));
        }
        last_x = 0;
    }

    //Back button
    auto backBtn = std::make_unique<Button>(ButtonType::WIDE);
    backBtn->setString("<-");
    backBtn->setColor(sf::Color::Transparent);
    backBtn->setPosition({10, 10});

    backBtn->setFunction([this](){
        m_pageWantExit = true;
    });

    m_pages[getCurrentPage()].addItem(std::move(backBtn));
    m_pages[getCurrentPage()].addItem(std::move(tit));
}

void MainMenuState::createErrorPopUp(const std::string &errorMsg){
    
}

} //namespace
