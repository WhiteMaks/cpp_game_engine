cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME cpp_game_engine)
project(${PROJECT_NAME})

enable_testing()

add_subdirectory(GameEngine)
add_subdirectory(Sandbox)
add_subdirectory(Tests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)