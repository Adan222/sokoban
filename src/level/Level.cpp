#include "Level.hpp"
#include "PlayerConfig.hpp"
#include "entities/Box.hpp"

Level::Level(SoundManager& soundManager,const std::filesystem::path& filename) : 
    m_levelConfig(filename),
    m_levelMap(m_levelConfig),
    m_physics(m_levelMap.find(WALL), m_boxes),
    m_winChecker(m_boxes, m_levelMap.find(WIN_PLACE, BOX_AND_WIN)),
    m_wantExit(false),
    m_soundManager(&soundManager),
    m_moves(0)
{   
    setEntitiesPosition();    
    m_levelMap.loadTexture();
    m_levelMap.createMap();


    initSound();
}


Level::Level(SoundManager& soundManager, PlayerConfig &playerConf) : 
    m_player(),
    m_levelConfig(playerConf),
    m_levelMap(m_levelConfig),
    m_physics(m_levelMap.find(WALL), m_boxes),
    m_winChecker(m_boxes, m_levelMap.find(WIN_PLACE, BOX_AND_WIN)),
    m_wantExit(false),
    m_moves(0),
    m_soundManager(&soundManager)
{
    setEntitiesPosition();

    m_levelMap.loadTexture();
    m_levelMap.createMap();
    
    initSound();

}

void Level::initSound() {
    
    m_soundManager->setFile<SoundManager::Type::Theme>("../" + m_levelConfig.getThemeSongPath().generic_string());
    m_soundManager->setFile<SoundManager::Type::PlayerEngine>("../res/sounds/player/engine.wav");
    m_soundManager->play<SoundManager::Type::Theme>();
    m_soundManager->play<SoundManager::Type::PlayerEngine>();

}


Level::~Level() {
    
    m_soundManager->stop<SoundManager::Type::Theme>();
    m_soundManager->stop<SoundManager::Type::PlayerEngine>();

}

void Level::iterate(std::function<void(int)> func) {
    for(int i = 0; i < m_boxes.size(); i++)
        func(i);
}

void Level::playerMove(DIRECTION dir) {
    m_player.move(dir);
    m_player.setAnimation(dir);
}

void Level::moveBox(DIRECTION dir) {
    iterate([&](int i){
        if(m_boxes[i].checkIfImChosen())
            m_boxes[i].move(dir);
    });
}

void Level::render(sf::RenderTarget& renderer) {
    //Map
    renderer.draw(m_levelMap);
    //Player
    renderer.draw(m_player);
    //Boxes
    for(const auto& i : m_boxes)
        renderer.draw(i);
}

void Level::input(const sf::Keyboard::Key pressedKey){
    handleMove(pressedKey);
}

void Level::savePlayerConfig(std::string &name, const int score) {
    auto logicGrid = m_levelConfig.getLogicGrid();
    auto tileSize = m_levelConfig.getTileSize();

    for(auto &i : logicGrid)
        if(i == LOGIC::BOX || i == LOGIC::PLAYER)
            i = LOGIC::FREE;
    uint32_t playerIndex =
        m_levelMap.positionToIndex(
            sf::Vector2f{float(m_player.getGridPos().x * tileSize), float(m_player.getGridPos().y * tileSize) });
                
    logicGrid[playerIndex] = LOGIC::PLAYER;

    for(const auto& box : m_boxes) {
        uint32_t boxIndex =
            m_levelMap.positionToIndex(sf::Vector2f{float(box.getGridPos().x * tileSize), float(box.getGridPos().y * tileSize)});
        logicGrid[boxIndex] = LOGIC::BOX;
    }

    m_levelConfig.getPlayerConfig().setMadeMoves(getMoves());
    m_levelConfig.getPlayerConfig().setScore(score);
    m_levelConfig.getPlayerConfig().setLogicGrid(logicGrid);
    m_levelConfig.getPlayerConfig().saveConfig(name, m_levelConfig.getJsonFilePath());
}

bool Level::checkIfWantExit() const {
    return m_wantExit;
}

int Level::getMoves() const {
    return m_moves;
}

void Level::handleMove(const sf::Keyboard::Key pressedKey){
    using Key = sf::Keyboard;

    DIRECTION dir = NONE;
    /*
     * Lock input while player is moving.
     */
    if(!m_player.isMoving()){
        if(pressedKey == Key::W){
            dir = UP;
        }

        if(pressedKey == Key::A){
            dir = LEFT;
        }

        if(pressedKey == Key::S){
            dir = DOWN;
        }

        if(pressedKey == Key::D){
            dir = RIGHT;
        }

        //move
        if(dir != NONE){

            //Check for wall
            if(!m_physics.checkWall(m_player.getGridPos(), dir)){
                //Then check for Box
                if(m_physics.checkBoxCollision(m_player.getGridPos(), dir)){
                    //And if there`s box, check for obscatle behind him
                    if(m_physics.chcekNextObscatle(m_player.getGridPos(), dir)){
                        std::cout << "Can`t move\n";
                    }
                    //If there`s no obscatle move player and box
                    else{
                        m_moves++;

                        //allow box to move
                        m_physics.action();

                        playerMove(dir);
                        moveBox(dir);
                    }
                }
                else{
                    playerMove(dir);
                    m_moves++;
                }
            }
        }        
        //now any box can move
        disappoint();

        //exit lvl
        if(m_player.isOnPlace())
            if(m_winChecker.check()){
                std::cout << "You win!!!\n";
                m_wantExit = true;
            }

    }
}

void Level::disappoint() {
    iterate([&](int i){
        m_boxes[i].imNotChosenOne();
    });
}

void Level::update(const float deltaTime){
    m_player.update(deltaTime);

    iterate([&](int i){
        m_boxes[i].update(deltaTime);
    });  
}

void Level::setEntitiesPosition(){
    Positions boxesPos = m_levelMap.find(BOX, BOX_AND_WIN);
    int am = boxesPos.size();

    m_boxes.resize(am);
    for(int i = 0; i < am; i++){
        int x = boxesPos[i].x;
        int y = boxesPos[i].y;

        m_boxes[i].initPosition(x, y);
    }
    
    //player position
    Positions playerPos = m_levelMap.find(PLAYER);
    m_player.initPosition(playerPos[0].x, playerPos[0].y);
}
