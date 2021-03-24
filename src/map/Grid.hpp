#pragma once

enum LOGIC {
    FREE,
    WALL,
    PLAYER,
    BOX,
    WIN_PLACE,
    BOX_AND_WIN
};

const unsigned short MAX_LOGIC = BOX_AND_WIN;