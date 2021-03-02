cmake_policy(SET CMP0079 NEW)
cmake_minimum_required(VERSION 3.13)

#must be above project
set(ImGui-SFML_DIR "${CMAKE_SOURCE_DIR}/lib/imgui-sfml/")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/lib/imgui/")

project(sokoban VERSION 0.0.0
                DESCRIPTION "Sokoban - Motorola Science Cup"
                LANGUAGES CXX)

#c++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#clangd specific
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)


#include path to src folder
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/src")

#json lib
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/lib/jsonlib/")

#imgui
find_package(ImGui-SFML REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)


#SFML LINUX
if(UNIX AND NOT APPLE)
    message(STATUS "Running on Linux")

    #include files for SFML lib
    target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/include")

    #include standard c++ lib, needed for clang
    target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include/c++/10.2.0")

    #link SFML lib
    file(GLOB SFML_LIB "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/lib/*.so")
    target_link_libraries(${PROJECT_NAME} PUBLIC "${SFML_LIB}")
endif() #UNIX AND NOT APPLE


#set Debug build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()