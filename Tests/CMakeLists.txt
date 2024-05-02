cmake_minimum_required(VERSION 3.22)

set(TESTS_PROJECT_NAME Tests)

add_executable(
	${TESTS_PROJECT_NAME}_Math
	src/MathTests.cpp
)

target_compile_features(${TESTS_PROJECT_NAME}_Math PUBLIC cxx_std_20)

set_target_properties(${TESTS_PROJECT_NAME}_Math PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

message(STATUS "GAME_ENGINE_PLATFORM = " $ENV{GAME_ENGINE_PLATFORM})

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	target_compile_definitions(GameEngine PUBLIC GAME_ENGINE_PLATFORM_WINDOWS)
endif()

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

target_link_libraries(${TESTS_PROJECT_NAME}_Math PRIVATE
	GTest::GTest 
	GameEngine
)

add_test(GameEngineTests_Math ${TESTS_PROJECT_NAME}_Math)
set_tests_properties(GameEngineTests_Math PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/)