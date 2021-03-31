set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

SET (SOURCE_FILES main.cpp
            PlayerConfig.hpp
            PlayerConfig.cpp
            Game.hpp
            Game.cpp
            gui/Pages.cpp
            gui/FpsCounter.hpp
            gui/FpsCounter.cpp
            gui/EditorGui.hpp
            gui/EditorGui.cpp
            gui/menu/wText.hpp
            gui/menu/wText.cpp
            gui/menu/Button.hpp
            gui/menu/Button.cpp
            gui/menu/Title.hpp
            gui/menu/Title.cpp
            gui/menu/Widget.hpp
            gui/menu/WidgetStack.hpp
            gui/menu/WidgetStack.cpp
            gui/menu/TextBox.hpp
            gui/menu/TextBox.cpp
            gui/ImGuiStyle.hpp
            states/State.hpp
            states/PlayingState.hpp
            states/PlayingState.cpp
            states/MainMenuState.hpp
            states/MainMenuState.cpp
            states/LevelEditorState.hpp
            states/LevelEditorState.cpp
            level/LevelConfig.hpp
            level/LevelConfig.cpp
            level/Level.hpp
            level/Level.cpp
            level/WinChecker.hpp
            level/WinChecker.cpp
            level/LevelEditor.hpp
            level/LevelEditor.cpp
            entities/Entity.hpp
            entities/Entity.cpp
            entities/Player.hpp
            entities/Player.cpp
            entities/animation/Animation.hpp
            entities/animation/Animation.cpp
            entities/animation/AnimationHandler.hpp
            entities/animation/AnimationHandler.cpp
            entities/guide/Guide.hpp
            entities/guide/Guide.cpp
            entities/Box.hpp
            entities/Box.cpp
            entities/physics/Physics.hpp
            entities/physics/Physics.cpp
            entities/physics/collisions/BoxCollisions.hpp
            entities/physics/collisions/BoxCollisions.cpp
            entities/physics/collisions/WallCollisions.hpp
            entities/physics/collisions/WallCollisions.cpp
            sound/SoundManager.hpp
            sound/SoundManager.cpp
            map/Map.hpp
            map/Map.cpp
            map/Tile.hpp
            map/Tile.cpp
            
    )
    
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)


