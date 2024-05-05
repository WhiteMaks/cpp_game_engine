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
	includes/Core/GraphicsEngine/GraphicsEngine.h
	includes/Core/GraphicsEngine/GraphicsAPI.h
	includes/Core/GraphicsEngine/Renderer/GraphicsContext.h
	includes/Core/GraphicsEngine/Renderer/GraphicsContextFactory.h
	includes/Core/GraphicsEngine/Renderer/ShaderProgram.h
	includes/Core/GraphicsEngine/Renderer/ShaderProgramFactory.h
	includes/Core/GraphicsEngine/Renderer/ShaderCodeFactory.h
	includes/Core/GraphicsEngine/Renderer/VertexStaticBuffer.h
	includes/Core/GraphicsEngine/Renderer/IndexStaticBuffer.h
	includes/Core/GraphicsEngine/Renderer/VertexArrayBuffer.h
	includes/Core/GraphicsEngine/Renderer/BufferFactory.h
	includes/Core/GraphicsEngine/Renderer/BufferLayout.h
	includes/Core/GraphicsEngine/Renderer/BufferElement.h
	includes/Core/GraphicsEngine/Renderer/BufferElementType.h
	includes/Core/GraphicsEngine/Renderer/Renderer.h
	includes/Core/GraphicsEngine/Renderer/RendererAPI.h
	includes/Core/GraphicsEngine/Renderer/RendererAPIFactory.h
	includes/Core/GraphicsEngine/Renderer/OrthographicCamera.h

	includes/Tools/Log.h
	includes/Tools/Layer.h
	includes/Tools/Time.h
	includes/Tools/LayerStack.h
	includes/Tools/Math/Vector.h
	includes/Tools/Math/Vector2.h
	includes/Tools/Math/Vector3.h
	includes/Tools/Math/Vector4.h
)

set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES "")

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES
		src/Core/Platform/Browser/BrowserWindow.h
		src/Core/Platform/Windows/WindowsWindow.h
		src/Core/Platform/Glfw/GlfwWindow.h

		src/Core/GraphicsEngine/WebGL/WebGLContext.h
		src/Core/GraphicsEngine/WebGL/WebGLShaderProgram.h
		src/Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLRenderer.h
		
		src/Core/GraphicsEngine/OpenGL/OpenGLContext.h
		src/Core/GraphicsEngine/OpenGL/OpenGLShaderProgram.h
		src/Core/GraphicsEngine/OpenGL/OpenGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLRenderer.h
		
		src/Core/GraphicsEngine/DirectX/DirectX11Context.h
		src/Core/GraphicsEngine/DirectX/DirectX12Context.h
	)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES
		src/Core/Platform/Browser/BrowserWindow.h
		src/Core/GraphicsEngine/WebGL/WebGLContext.h
		src/Core/GraphicsEngine/WebGL/WebGLShaderProgram.h
		src/Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLRenderer.h
	)
endif()

set(GAME_ENGINE_PRIVATE_INCLUDES
	src/ExitCodes.h

	${GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES}
)

set(GAME_ENGINE_PRIVATE_PLATFORM_SOURCES "")

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	set(GAME_ENGINE_PRIVATE_PLATFORM_SOURCES
		src/Core/Platform/Browser/BrowserWindow.cpp
		src/Core/Platform/Windows/WindowsWindow.cpp
		src/Core/Platform/Glfw/GlfwWindow.cpp

		src/Core/GraphicsEngine/WebGL/WebGLContext.cpp
		src/Core/GraphicsEngine/WebGL/WebGLShaderProgram.cpp
		src/Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLRenderer.cpp

		src/Core/GraphicsEngine/OpenGL/OpenGLContext.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLShaderProgram.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexArrayBuffer.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLRenderer.cpp
		
		src/Core/GraphicsEngine/DirectX/DirectX11Context.cpp
		src/Core/GraphicsEngine/DirectX/DirectX12Context.cpp	
	)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	set(GAME_ENGINE_PRIVATE_PLATFORM_SOURCES
		src/Core/Platform/Browser/BrowserWindow.cpp
		src/Core/GraphicsEngine/WebGL/WebGLContext.cpp
		src/Core/GraphicsEngine/WebGL/WebGLShaderProgram.cpp
		src/Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLRenderer.cpp
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
	src/Core/GraphicsEngine/GraphicsEngine.cpp
	src/Core/GraphicsEngine/Renderer/GraphicsContext.cpp
	src/Core/GraphicsEngine/Renderer/GraphicsContextFactory.cpp
	src/Core/GraphicsEngine/Renderer/ShaderProgram.cpp
	src/Core/GraphicsEngine/Renderer/ShaderProgramFactory.cpp
	src/Core/GraphicsEngine/Renderer/ShaderCodeFactory.cpp
	src/Core/GraphicsEngine/Renderer/VertexStaticBuffer.cpp
	src/Core/GraphicsEngine/Renderer/IndexStaticBuffer.cpp
	src/Core/GraphicsEngine/Renderer/VertexArrayBuffer.cpp
	src/Core/GraphicsEngine/Renderer/BufferFactory.cpp
	src/Core/GraphicsEngine/Renderer/BufferLayout.cpp
	src/Core/GraphicsEngine/Renderer/BufferElement.cpp
	src/Core/GraphicsEngine/Renderer/Renderer.cpp
	src/Core/GraphicsEngine/Renderer/RendererAPI.cpp
	src/Core/GraphicsEngine/Renderer/RendererAPIFactory.cpp
	src/Core/GraphicsEngine/Renderer/OrthographicCamera.cpp

	${GAME_ENGINE_PRIVATE_PLATFORM_SOURCES}

	src/Tools/Log.cpp
	src/Tools/Layer.cpp
	src/Tools/Time.cpp
	src/Tools/LayerStack.cpp
	src/Tools/Math/Vector.cpp
	src/Tools/Math/Vector2.cpp
	src/Tools/Math/Vector3.cpp
	src/Tools/Math/Vector4.cpp
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

add_subdirectory(./vendor/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PUBLIC glm)

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	add_subdirectory(./vendor/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glad)

	add_subdirectory(./vendor/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glfw)
	
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE OpenGL32.lib)

	add_subdirectory(./vendor/sdl ${CMAKE_CURRENT_BINARY_DIR}/sdl)
	target_include_directories(${GAME_ENGINE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl/include)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE SDL2::SDL2)

	#add_custom_command(TARGET ${GAME_ENGINE_PROJECT_NAME} POST_BUILD
	#	COMMAND ${CMAKE_COMMAND} -E copy
	#	$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2d.dll
	#	$<TARGET_FILE_DIR:${GAME_ENGINE_PROJECT_NAME}>
	#)
elseif($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	add_subdirectory(./vendor/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glad)

	add_subdirectory(./vendor/sdl ${CMAKE_CURRENT_BINARY_DIR}/sdl)
	target_include_directories(${GAME_ENGINE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl/include)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE SDL2::SDL2)
endif()

set_target_properties(${GAME_ENGINE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_definitions(-DGAME_ENGINE_BUILD_DLL -D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)