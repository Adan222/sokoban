#set executable path to build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

#add all source files to executable
file(GLOB SRC "*.cpp" "*.hpp")
add_executable(${PROJECT_NAME} ${SRC})