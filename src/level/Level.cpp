#include "Level.hpp"

Level::Level(const std::string& filename) : 
    m_levelConfig(filename),
    m_player(),
    m_t1(m_levelConfig),
    m_physics(m_walls, m_boxes),
    m_boxesAmount(0)
{   
    setEntitiesPosition();
    m_walls = m_t1.getWallsPos();
}

Level::~Level() {}

void Level::iterate(function func) {
    //int am = m_levelConfig.getBoxesAmount();
    //for(int i = 0; i < am; i++)
        //func(i);
}

void Level::playerMove(DIRECTION dir) {
    m_player.move(dir);
    m_player.setAniamtion(dir);
}

void Level::boxMove(DIRECTION dir) {
    int am = m_boxesAmount;
    for(int i = 0; i < am; i++)
        if(m_boxes[i].checkIfImChosen())
            m_boxes[i].move(dir);
}

void Level::render(sf::RenderTarget& renderer) {

    //Map
    renderer.draw(m_t1);
    //Player
    renderer.draw(m_player);
    //Boxes
    int am = m_boxesAmount;
    for(int i = 0; i < am; i++)
        renderer.draw(m_boxes[i]);
}

void Level::input(const sf::Keyboard::Key pressedKey){
    handleMove(pressedKey);
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
            if(!m_physics.checkWall(m_player.getGridPos(), dir)){
                if(m_physics.checkBoxCollision(m_player.getGridPos(), dir)){
                    if(m_physics.chcekNextObscatle(m_player.getGridPos(), dir)){
                        std::cout << "Can`t move\n";
                    }
                    else{
                        m_physics.action();
                        playerMove(dir);
                        boxMove(dir);
                    }
                }
                else{
                    playerMove(dir);
                }
            }
        }
        disappoint();
    }
}

void Level::moveBoxes(DIRECTION dir) {
    int am = m_boxesAmount;
    for(int i = 0; i < am; i++)
        m_boxes[i].move(dir);
}

void Level::disappoint() {
    int am = m_boxesAmount;
    for(int i = 0; i < am; i++)
        m_boxes[i].imNotChosenOne();
}

void Level::update(const float deltaTime){
    m_player.update(deltaTime);

    int am = m_boxesAmount;
    for(int i = 0; i < am; i++)
        m_boxes[i].update(deltaTime);
}

void Level::setEntitiesPosition(){
    Positions boxesPos = m_t1.getBoxesPos();
    m_boxesAmount = m_t1.getBoxesAmount();

    m_boxes.resize(m_boxesAmount);
    int am = m_boxesAmount;
    for(int i = 0; i < am; i++){
        int x = boxesPos[i].x;
        int y = boxesPos[i].y;

        m_boxes[i].initPosition(x, y);
    }
    
    int x = m_t1.getPlayerPos().x;
    int y = m_t1.getPlayerPos().y;
    m_player.initPosition(x, y);
}
