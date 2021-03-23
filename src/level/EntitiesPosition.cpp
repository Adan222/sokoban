#include "EntitiesPosition.hpp"

EntitiesPosition::EntitiesPosition(const LevelConfig &lvlcfg) :
    LogicalGrid(lvlcfg),
    m_boxAmount(0)
{
    int am = m_logicalGrid.size();
    for(int i = 0; i < am; i++){
        if(m_logicalGrid[i] == LOGIC::BOX ||
        m_logicalGrid[i] == LOGIC::BOX_AND_WIN){
            m_boxesPos.emplace_back(indexToPos(i));
            m_boxAmount++;
        }
        if(m_logicalGrid[i] == LOGIC::PLAYER)
            m_playerPos = indexToPos(i);
    }
}

EntitiesPosition::~EntitiesPosition() {}

BoxesPos EntitiesPosition::getBoxesPos() const {
    return m_boxesPos;
}

sf::Vector2i EntitiesPosition::getPlayerPos() const {
    return m_playerPos;
}

int EntitiesPosition::getBoxesAmount() const {
    return m_boxAmount;
}

