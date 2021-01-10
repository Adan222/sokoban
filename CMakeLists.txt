#CMAKE_SOURCE_DIR = sfml/
#CMAKE_BINARY_DIR = sfml/build


cmake_minimum_required(VERSION 3.10)


project(SFML VERSION 0.0.0)


#specify c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


#set executable path to build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")


#this is for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


configure_file(projConfig.hpp.in "${CMAKE_SOURCE_DIR}/src/projConfig.hpp")


add_executable(sfml "${CMAKE_SOURCE_DIR}/src/main.cpp")


#add include path to src folder
target_include_directories(sfml PUBLIC "${CMAKE_SOURCE_DIR}/src")

#LINUX
if(UNIX AND NOT APPLE)
    message(STATUS "Running on Linux")

    #include files for SFML lib
    target_include_directories(sfml PUBLIC "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/include")

    #include standard c++ lib
    #it` only for my clnagd couse it dont` see std lib
    target_include_directories(sfml PUBLIC "/usr/include/c++/10.2.0")

    #link SFML lib
    target_link_libraries(sfml "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/lib/libsfml-audio.so")
    target_link_libraries(sfml "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/lib/libsfml-graphics.so")
    target_link_libraries(sfml "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/lib/libsfml-network.so")
    target_link_libraries(sfml "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/lib/libsfml-system.so")
    target_link_libraries(sfml "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/lib/libsfml-window.so")

endif()
