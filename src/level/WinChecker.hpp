#pragma once

#include "level/LevelConfig.hpp"
#include "logicalGrid/LogicalGrid.hpp"

class WinChecker{
    private:
        BoxesPos &m_boxes;
    public:
        WinChecker(BoxesPos &boxes);
        ~WinChecker();

        bool winCheck();
};