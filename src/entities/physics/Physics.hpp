#pragma once

#include "entities/physics/collisions/WallCollisions.hpp"
#include "level/LevelConfig.hpp"
#include "entities/Box.hpp"
#include "collisions/BoxCollisions.hpp"
#include "entities/guide/Guide.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>

class Physics{
    private:
        BoxCollisions m_boxCollisions;
        WallCollisions m_wallCollision;

        /*
         * Iterate component depend on direction
         */
        void makeNext(sf::Vector2i &vec, DIRECTION d, const int i);

        sf::Vector2i currPlayerPos;

    public:
        Physics(const Positions walls, Boxes &allboxes);
        ~Physics();

        void init(const Positions walls, Boxes &allboxes);
        /*
         * Chcek for wall on next move.
         * Return true if there is wall 
         */
        bool checkWall(const sf::Vector2i currPos, DIRECTION dir);

        /*
         * Chcek collison with box.
         * Return true if box is next to
         */
        bool checkBoxCollision(const sf::Vector2i currPos, DIRECTION dir);

        /*
         * Check for obscatle behind box, that is
         * next box or wall
         */
        bool chcekNextObscatle(const sf::Vector2i currPos, DIRECTION dir);

        void action();
};