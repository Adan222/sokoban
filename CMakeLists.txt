#this project is using vcpkg as dependecy manager please use build.sh for building
cmake_minimum_required(VERSION 3.15)

project(sokoban VERSION 0.0.5
                DESCRIPTION "Sokoban - Motorola Science Cup"
                LANGUAGES CXX)

include(${CMAKE_SOURCE_DIR}/cmake/prevent_in_source_builds.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ccache.cmake)

add_library(project_warnings INTERFACE)
include(${CMAKE_SOURCE_DIR}/cmake/compiler_warings.cmake)
set_project_warnings(project_warnings)

if(NOT VCPKG_CHAINLOAD_TOOLCHAIN_FILE)
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
endif()


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

#c++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

find_package(soloud CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(SFML COMPONENTS  system window graphics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)

target_link_libraries(sokoban PRIVATE soloud)
target_link_libraries(sokoban PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(sokoban PRIVATE sfml-system sfml-graphics sfml-window)
target_link_libraries(sokoban PRIVATE imgui::imgui)
target_link_libraries(sokoban PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(sokoban PRIVATE unofficial::nativefiledialog::nfd)


