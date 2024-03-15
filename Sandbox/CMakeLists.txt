cmake_minimum_required(VERSION 3.22)

set(SANDBOX_PROJECT_NAME Sandbox)

add_executable(
	${SANDBOX_PROJECT_NAME}
	src/Sandbox.cpp
)

target_link_libraries(${SANDBOX_PROJECT_NAME} 
	GameEngine
)

target_compile_features(${SANDBOX_PROJECT_NAME} PUBLIC cxx_std_20)

set_target_properties(${SANDBOX_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

message(STATUS "GAME_ENGINE_PLATFORM = " $ENV{GAME_ENGINE_PLATFORM})

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
    target_compile_definitions(GameEngine PUBLIC GAME_ENGINE_PLATFORM_WINDOWS)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
    target_compile_definitions(GameEngine PUBLIC GAME_ENGINE_PLATFORM_BROWSER)
endif()