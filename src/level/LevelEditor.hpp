#pragma once 

#include "SFML/Graphics.hpp"
#include "level/LevelConfig.hpp"
#include "gui/EditorGui.hpp"
#include "map/Map.hpp"
#include <nfd.h>

class LevelEditor {
    std::reference_wrapper<LevelConfig> m_levelConfig; 
    
    Map m_m1;
    EditorGui m_editorGui;


    sf::RenderStates m_attachedTextureRS;

public:
    LevelEditor(LevelConfig& levelConfig);
    LevelEditor(LevelConfig& levelConfig, bool initialPopupShowed);


    ~LevelEditor();

    bool wantsReload() const;

    void render(sf::RenderTarget& renderer);
    void update(const float deltaTime);
    void input(sf::Event e);

};