cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME stb)
project(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC stb_image.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})