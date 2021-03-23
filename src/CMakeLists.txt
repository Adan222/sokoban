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
            level/LevelConfig.hpp
            level/LevelConfig.cpp
            logicalGrid/LogicalGrid.hpp
            level/EntitiesPosition.hpp
            level/EntitiesPosition.cpp
            level/Level.hpp
            level/Level.cpp
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
            map/Grid.hpp
            map/Grid.cpp
            map/Map.hpp
            map/Map.cpp
    )
    
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)


