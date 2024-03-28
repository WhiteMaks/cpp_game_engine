cmake_minimum_required(VERSION 3.22)

set(GAME_ENGINE_PROJECT_NAME GameEngine)

set(GAME_ENGINE_PUBLIC_INCLUDES
	includes/GameEngine.h

	includes/Core/Core.h
	
	includes/Core/EventsSystem/Keyboard.h
	includes/Core/EventsSystem/KeyboardEvent.h
	includes/Core/EventsSystem/KeyboardEventType.h
	includes/Core/EventsSystem/Mouse.h
	includes/Core/EventsSystem/MouseEvent.h
	includes/Core/EventsSystem/MouseEventType.h
	includes/Core/EventsSystem/Window.h
	includes/Core/EventsSystem/WindowEvent.h
	includes/Core/EventsSystem/WindowEventType.h
	includes/Core/EventsSystem/EventManager.h

	includes/Core/GraphicsEngine/Window.h
	includes/Core/GraphicsEngine/WindowFactory.h

	includes/Tools/Log.h
	includes/Tools/Layer.h
	includes/Tools/LayerStack.h
)

set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES "")

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES
		src/Core/Platform/WindowsWindow.h
		#src/Core/Platform/BrowserWindow.h
	)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES
		src/Core/Platform/BrowserWindow.h
	)
endif()

set(GAME_ENGINE_PRIVATE_INCLUDES
	src/ExitCodes.h

	${GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES}
)

set(GAME_ENGINE_PRIVATE_PLATFOR_SOURCES "")

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	set(GAME_ENGINE_PRIVATE_PLATFOR_SOURCES
		src/Core/Platform/WindowsWindow.cpp
		#src/Core/Platform/BrowserWindow.cpp
	)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	set(GAME_ENGINE_PRIVATE_PLATFOR_SOURCES
		src/Core/Platform/BrowserWindow.cpp
	)
endif()

set(GAME_ENGINE_PRIVATE_SOURCES
	src/GameEngine.cpp
	
	src/Core/EventsSystem/Keyboard.cpp
	src/Core/EventsSystem/KeyboardEvent.cpp
	src/Core/EventsSystem/Mouse.cpp
	src/Core/EventsSystem/MouseEvent.cpp
	src/Core/EventsSystem/Window.cpp
	src/Core/EventsSystem/WindowEvent.cpp
	src/Core/EventsSystem/EventManager.cpp

	src/Core/GraphicsEngine/Window.cpp
	src/Core/GraphicsEngine/WindowFactory.cpp

	${GAME_ENGINE_PRIVATE_PLATFOR_SOURCES}

	src/Tools/Log.cpp
	src/Tools/Layer.cpp
	src/Tools/LayerStack.cpp
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

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	add_subdirectory(./vendor/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glfw)

	add_subdirectory(./vendor/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glad)
elseif($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	add_subdirectory(./vendor/sdl ${CMAKE_CURRENT_BINARY_DIR}/sdl)
	target_include_directories(${GAME_ENGINE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl/include)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE SDL2::SDL2)
endif()

set_target_properties(${GAME_ENGINE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_definitions(-DGAME_ENGINE_BUILD_DLL -D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)