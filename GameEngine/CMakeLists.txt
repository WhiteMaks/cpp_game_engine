cmake_minimum_required(VERSION 3.22)

set(GAME_ENGINE_PROJECT_NAME GameEngine)

set(GAME_ENGINE_PUBLIC_INCLUDES
	includes/GameEngine.h
	includes/Engine/Engine.h

	includes/Engine/Support/Core.h
	includes/Engine/Support/Log.h
	
	includes/Engine/EventsSystem/Keyboard.h
	includes/Engine/EventsSystem/KeyboardEvent.h
	includes/Engine/EventsSystem/KeyboardEventType.h
	includes/Engine/EventsSystem/Mouse.h
	includes/Engine/EventsSystem/MouseEvent.h
	includes/Engine/EventsSystem/MouseEventType.h
)

set(GAME_ENGINE_PRIVATE_INCLUDES
	
)

set(GAME_ENGINE_PRIVATE_SOURCES
	src/Engine/Engine.cpp
	
	src/Engine/Support/Log.cpp
	
	src/Engine/EventsSystem/Keyboard.cpp
	src/Engine/EventsSystem/KeyboardEvent.cpp
	src/Engine/EventsSystem/Mouse.cpp
	src/Engine/EventsSystem/MouseEvent.cpp
)

set(GAME_ENGINE_ALL_SOURCES
	${GAME_ENGINE_PUBLIC_INCLUDES}

	${GAME_ENGINE_PRIVATE_INCLUDES}
	${GAME_ENGINE_PRIVATE_SOURCES}
)

add_library(${GAME_ENGINE_PROJECT_NAME} SHARED 
	${GAME_ENGINE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${GAME_ENGINE_ALL_SOURCES}
)

target_include_directories(${GAME_ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${GAME_ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${GAME_ENGINE_PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(./vendor/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PUBLIC spdlog)

set_target_properties(${GAME_ENGINE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_definitions(-DGAME_ENGINE_BUILD_DLL)