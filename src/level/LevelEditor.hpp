#pragma once 

#include "SFML/Graphics.hpp"
#include "level/LevelConfig.hpp"
#include "gui/EditorGui.hpp"
#include "map/Map.hpp"
#include <nfd.h>

class LevelEditor {
    LevelConfig m_levelConfig;    
    EditorGui m_editorGui;

    Map m_m1;

    sf::RenderStates m_attachedTextureRS;

public:
    LevelEditor(LevelConfig levelConfig, bool initialPopupShowed);
    ~LevelEditor();

    void render(sf::RenderTarget& renderer);
    void update(const float deltaTime,  std::filesystem::path& jsonPath);
    void input(sf::Event e);

};