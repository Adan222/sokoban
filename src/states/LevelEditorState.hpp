#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "State.hpp"
#include "../LevelConfig.hpp"
#include "../map/Map.hpp"
#include "../Game.hpp"

namespace State {


class LevelEditorState : public State {
    uint16_t atlasTileSize;
    
    void tileSelectionBox();
 
    LevelConfig m_levelConfig;
    Map m_m1;
public:
    LevelEditorState(Game& game);
    ~LevelEditorState();

    void handleEvent(sf::Event e) override;
    void draw(sf::RenderTarget& renderer) override;
    
    void pause() override;
    void resume() override;
};


} //namespace State