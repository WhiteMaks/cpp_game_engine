cmake_minimum_required(VERSION 3.22)

set(GAME_ENGINE_PROJECT_NAME GameEngine)

set(GAME_ENGINE_PUBLIC_INCLUDES
	includes/GameEngine.h

	includes/Core/Core.h
	includes/Core/OrthographicCameraController.h
	
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
	includes/Core/GraphicsEngine/Renderer/Renderer.h
	includes/Core/GraphicsEngine/Renderer/Renderer2D.h
	includes/Core/GraphicsEngine/Renderer/RendererAPI.h
	includes/Core/GraphicsEngine/Renderer/RendererAPIFactory.h
	includes/Core/GraphicsEngine/Renderer/OrthographicCamera.h

	includes/Core/GraphicsEngine/Renderer/Buffers/FrameBuffer.h
	includes/Core/GraphicsEngine/Renderer/Buffers/FrameBufferData.h
	includes/Core/GraphicsEngine/Renderer/Buffers/VertexStaticBuffer.h
	includes/Core/GraphicsEngine/Renderer/Buffers/VertexDynamicBuffer.h
	includes/Core/GraphicsEngine/Renderer/Buffers/IndexStaticBuffer.h
	includes/Core/GraphicsEngine/Renderer/Buffers/VertexArrayBuffer.h
	includes/Core/GraphicsEngine/Renderer/Buffers/BufferFactory.h
	includes/Core/GraphicsEngine/Renderer/Buffers/BufferLayout.h
	includes/Core/GraphicsEngine/Renderer/Buffers/BufferElement.h
	includes/Core/GraphicsEngine/Renderer/Buffers/BufferElementType.h

	includes/Core/GraphicsEngine/Assets/Sprite.h
	includes/Core/GraphicsEngine/Assets/Spritesheet.h
	includes/Core/GraphicsEngine/Assets/Texture.h
	includes/Core/GraphicsEngine/Assets/TextureFactory.h
	includes/Core/GraphicsEngine/Assets/ShaderProgram.h
	includes/Core/GraphicsEngine/Assets/ShaderProgramFactory.h

	includes/Tools/Log.h
	includes/Tools/Layer.h
	includes/Tools/Time.h
	includes/Tools/LayerStack.h
	includes/Tools/Math/Vector.h
	includes/Tools/Math/Vector2.h
	includes/Tools/Math/Vector3.h
	includes/Tools/Math/Vector4.h
	includes/Tools/Memory/CacheStorage.h
	includes/Tools/Memory/TimedCache.h
)

set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES "")

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES
		src/Core/Platform/Browser/BrowserWindow.h
		src/Core/Platform/Windows/WindowsWindow.h
		src/Core/Platform/Glfw/GlfwWindow.h

		src/Core/GraphicsEngine/WebGL/WebGLContext.h
		src/Core/GraphicsEngine/WebGL/WebGLShaderProgram.h
		src/Core/GraphicsEngine/WebGL/WebGLFrameBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexDynamicBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLRenderer.h
		src/Core/GraphicsEngine/WebGL/WebGLTexture.h
		
		src/Core/GraphicsEngine/OpenGL/OpenGLContext.h
		src/Core/GraphicsEngine/OpenGL/OpenGLShaderProgram.h
		src/Core/GraphicsEngine/OpenGL/OpenGLFrameBuffer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexDynamicBuffer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLRenderer.h
		src/Core/GraphicsEngine/OpenGL/OpenGLTexture.h
		
		#src/Core/GraphicsEngine/DirectX/DirectX11Context.h
		#src/Core/GraphicsEngine/DirectX/DirectX12Context.h
	)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES
		src/Core/Platform/Browser/BrowserWindow.h
		src/Core/GraphicsEngine/WebGL/WebGLContext.h
		src/Core/GraphicsEngine/WebGL/WebGLShaderProgram.h
		src/Core/GraphicsEngine/WebGL/WebGLFrameBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexDynamicBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/WebGL/WebGLRenderer.h
		src/Core/GraphicsEngine/WebGL/WebGLTexture.h
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
		src/Core/GraphicsEngine/WebGL/WebGLRenderer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLTexture.cpp
		src/Core/GraphicsEngine/WebGL/WebGLFrameBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexDynamicBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.cpp

		src/Core/GraphicsEngine/OpenGL/OpenGLContext.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLShaderProgram.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLRenderer.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLTexture.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLFrameBuffer.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexDynamicBuffer.cpp
		src/Core/GraphicsEngine/OpenGL/OpenGLVertexArrayBuffer.cpp
		
		#src/Core/GraphicsEngine/DirectX/DirectX11Context.cpp
		#src/Core/GraphicsEngine/DirectX/DirectX12Context.cpp	
	)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	set(GAME_ENGINE_PRIVATE_PLATFORM_SOURCES
		src/Core/Platform/Browser/BrowserWindow.cpp
		src/Core/GraphicsEngine/WebGL/WebGLContext.cpp
		src/Core/GraphicsEngine/WebGL/WebGLShaderProgram.cpp
		src/Core/GraphicsEngine/WebGL/WebGLFrameBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexDynamicBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLRenderer.cpp
		src/Core/GraphicsEngine/WebGL/WebGLTexture.cpp
	)
endif()

set(GAME_ENGINE_PRIVATE_SOURCES
	src/GameEngine.cpp

	src/Core/OrthographicCameraController.cpp
	
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
	src/Core/GraphicsEngine/Renderer/Renderer.cpp
	src/Core/GraphicsEngine/Renderer/Renderer2D.cpp
	src/Core/GraphicsEngine/Renderer/RendererAPI.cpp
	src/Core/GraphicsEngine/Renderer/RendererAPIFactory.cpp
	src/Core/GraphicsEngine/Renderer/OrthographicCamera.cpp

	src/Core/GraphicsEngine/Renderer/Buffers/FrameBuffer.cpp
	src/Core/GraphicsEngine/Renderer/Buffers/VertexStaticBuffer.cpp
	src/Core/GraphicsEngine/Renderer/Buffers/VertexDynamicBuffer.cpp
	src/Core/GraphicsEngine/Renderer/Buffers/IndexStaticBuffer.cpp
	src/Core/GraphicsEngine/Renderer/Buffers/VertexArrayBuffer.cpp
	src/Core/GraphicsEngine/Renderer/Buffers/BufferFactory.cpp
	src/Core/GraphicsEngine/Renderer/Buffers/BufferLayout.cpp
	src/Core/GraphicsEngine/Renderer/Buffers/BufferElement.cpp

	src/Core/GraphicsEngine/Assets/Sprite.cpp
	src/Core/GraphicsEngine/Assets/Spritesheet.cpp
	src/Core/GraphicsEngine/Assets/Texture.cpp
	src/Core/GraphicsEngine/Assets/TextureFactory.cpp
	src/Core/GraphicsEngine/Assets/ShaderProgram.cpp
	src/Core/GraphicsEngine/Assets/ShaderProgramFactory.cpp

	${GAME_ENGINE_PRIVATE_PLATFORM_SOURCES}

	src/Tools/Log.cpp
	src/Tools/Layer.cpp
	src/Tools/Time.cpp
	src/Tools/LayerStack.cpp
	src/Tools/Math/Vector.cpp
	src/Tools/Math/Vector2.cpp
	src/Tools/Math/Vector3.cpp
	src/Tools/Math/Vector4.cpp
	src/Tools/Memory/CacheStorage.cpp
	src/Tools/Memory/TimedCache.cpp
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

add_subdirectory(./vendor/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(./vendor/stb ${CMAKE_CURRENT_BINARY_DIR}/stb)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE stb)

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	add_subdirectory(./vendor/sdl ${CMAKE_CURRENT_BINARY_DIR}/sdl)
	target_include_directories(${GAME_ENGINE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl/include)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE SDL2::SDL2)

	add_subdirectory(./vendor/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glfw)
	
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE OpenGL32.lib)

	add_custom_command(TARGET ${GAME_ENGINE_PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2d.dll
		$<TARGET_FILE_DIR:${GAME_ENGINE_PROJECT_NAME}>
	)
elseif($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	target_compile_options(${GAME_ENGINE_PROJECT_NAME} PRIVATE
		-matomics
		-mbulk-memory
	)
	target_link_options(${GAME_ENGINE_PROJECT_NAME} PRIVATE
		-matomics
		-mbulk-memory
	)

	target_compile_options(spdlog PRIVATE
		-matomics
		-mbulk-memory
	)
	target_link_options(spdlog PRIVATE
		-matomics
		-mbulk-memory
	)

	target_compile_options(stb PRIVATE
		-matomics
		-mbulk-memory
	)
	target_link_options(stb PRIVATE
		-matomics
		-mbulk-memory
	)

	target_include_directories(${GAME_ENGINE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl/include)
endif()

set_target_properties(${GAME_ENGINE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_definitions(-DGAME_ENGINE_BUILD_DLL -D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)