#pragma once

#include "level/LevelConfig.hpp"
#include "entities/Box.hpp"

#include <SFML/System/Vector2.hpp>

class WinChecker{
    private:
        Boxes &m_boxes;
        const Positions m_winPlaces;
    public:
        WinChecker(Boxes &boxes, const Positions winPlaces);
        ~WinChecker();

        bool check() const;
};