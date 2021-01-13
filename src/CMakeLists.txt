#set executable path to build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_subdirectory(states)

#file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.hpp)
#GLOB/GLOB_RECURSE is bad practice if project is maintained by more than one person

SET (SOURCE_FILES main.cpp
            Game.hpp
            Game.cpp
            states/State.hpp
            states/PlayingState.hpp
            states/PlayingState.cpp)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})