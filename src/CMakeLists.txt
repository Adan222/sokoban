set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_subdirectory(states)

SET (SOURCE_FILES main.cpp
            Game.hpp
            Game.cpp
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
            map/Map.hpp
            map/Map.cpp
    )
    
add_executable(${PROJECT_NAME} ${SOURCE_FILES})