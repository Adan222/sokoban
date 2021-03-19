set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

SET (SOURCE_FILES main.cpp
            Game.hpp
            Game.cpp
            gui/FpsCounter.hpp
            gui/FpsCounter.cpp
            states/State.hpp
            states/PlayingState.hpp
            states/PlayingState.cpp
            states/MainMenuState.hpp
            states/MainMenuState.cpp
            states/LevelEditorState.hpp
            states/LevelEditorState.cpp
            Level.hpp
            Level.cpp
            LevelConfig.hpp
            LevelConfig.cpp
            entities/Player.hpp
            entities/Player.cpp
            entities/animation/Animation.hpp
            entities/animation/Animation.cpp
            entities/animation/PlayerAnimation.hpp
            entities/animation/PlayerAnimation.cpp
            entities/guide/PlayerGuide.hpp
            entities/guide/PlayerGuide.cpp
            entities/Box.hpp
            entities/Box.cpp
            map/Grid.hpp
            map/Grid.cpp
            map/Map.hpp
            map/Map.cpp
    )
    
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)


