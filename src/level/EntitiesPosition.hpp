#pragma once

#include "logicalGrid/LogicalGrid.hpp"

#include <SFML/System/Vector2.hpp>

typedef std::vector<sf::Vector2i> BoxesPos;

/*
 * This class searching for boxes and player
 * on logical_grid in JSON.
 * It`s temporary class, it will be created
 * only once on entities position init
 */
class EntitiesPosition : public LogicalGrid
{
    private:
        BoxesPos m_boxesPos;
        sf::Vector2i m_playerPos;

        int m_boxAmount;
    public:
        /*
         * We`re looking for entities in constructor
         */
        EntitiesPosition(const LevelConfig &lvlcfg);
        ~EntitiesPosition();

        BoxesPos getBoxesPos() const;
        sf::Vector2i getPlayerPos() const;

        int getBoxesAmount() const;
};
