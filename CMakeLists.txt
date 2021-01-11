#CMAKE_SOURCE_DIR = sfml/
#CMAKE_BINARY_DIR = sfml/build

cmake_policy(SET CMP0079 NEW)


cmake_minimum_required(VERSION 3.13)


project(sfml VERSION 0.0.0)


#specify c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


#this is for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


configure_file(config.hpp.in "${CMAKE_SOURCE_DIR}/src/config.hpp")


add_subdirectory(src)


#add include path to src folder
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/src")

#LINUX
if(UNIX AND NOT APPLE)
    message(STATUS "Running on Linux")

    #include files for SFML lib
    target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/include")

    #include standard c++ lib
    #it` only for my clnagd couse it dont` see std lib
    target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include/c++/10.2.0")

    #link SFML lib
    file(GLOB SFML_LIB "${CMAKE_SOURCE_DIR}/lib/linux/SFML-2.5.1/lib/*.so")
    target_link_libraries(${PROJECT_NAME} "${SFML_LIB}")

    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        message(STATUS "CCache found")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    else()
        message(STATUS "CCache not found")
    endif()

endif() #UNIX AND NOT APPLE

#set Debug build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

