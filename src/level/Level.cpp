#include "Level.hpp"
#include "level/EntitiesPosition.hpp"

Level::Level(const std::string& filename) : 
    m_levelConfig(filename),
    m_player(),
    m_physics(m_levelConfig, m_boxes),
    m_t1(m_levelConfig),
    m_grid(m_levelConfig),
    m_boxesAmount(0)
{   
    initMap();
    setEntitisPosition();
}

Level::~Level() {}

void Level::iterate(function func) {
    //int am = m_levelConfig.getBoxesAmount();
    //for(int i = 0; i < am; i++)
        //func(i);
}

void Level::render(sf::RenderTarget& renderer) {

    //grid
    renderer.draw(m_grid);
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
                    m_player.move(dir);
                    m_player.setAniamtion(dir);
                }
            }
            else{
                m_player.move(dir);
                m_player.setAniamtion(dir);
            }
        }
    }
}

void Level::moveBoxes(DIRECTION dir) {
    int am = m_boxesAmount;
    for(int i = 0; i < am; i++)
        m_boxes[i].move(dir);
}

void Level::disappoint() {
    for(auto &i : m_boxes)
        i.imNotChosenOne();
}

void Level::update(const float deltaTime){
    m_player.update(deltaTime);

    int am = m_boxesAmount;
    for(int i = 0; i < am; i++)
        m_boxes[i].update(deltaTime);
}

void Level::initMap(){
    m_t1.loadTexture();
    m_t1.createMap();
}

void Level::setEntitisPosition(){
    EntitiesPosition pos(m_levelConfig);

    const BoxesPos boxes = pos.getBoxesPos();
    m_boxesAmount = pos.getBoxesAmount();

    for(int i = 0; i < m_boxesAmount; i++){
        int x = boxes[i].x;
        int y = boxes[i].y;
        m_boxes[i].initPosition(x, y);
    }

    int x = pos.getPlayerPos().x;
    int y = pos.getPlayerPos().y;
    m_player.initPosition(x, y);
}
