cmake_minimum_required(VERSION 3.22)

set(GAME_ENGINE_PROJECT_NAME GameEngine)

set(GAME_ENGINE_PUBLIC_INCLUDES
	includes/GameEngine.h

	includes/Core/Core.h

	includes/Core/GraphicsEngine/Window.h
	includes/Core/GraphicsEngine/WindowFactory.h
	includes/Core/GraphicsEngine/GraphicsEngine.h
	includes/Core/GraphicsEngine/GraphicsAPI.h

	includes/Core/GraphicsEngine/Library/GraphicsLibrary.h
	includes/Core/GraphicsEngine/Library/GraphicsLibraryFactory.h
	includes/Core/GraphicsEngine/Library/GraphicsContext.h
	includes/Core/GraphicsEngine/Library/RendererAPI.h
	includes/Core/GraphicsEngine/Library/ShaderProgram.h
	includes/Core/GraphicsEngine/Library/Texture.h
	includes/Core/GraphicsEngine/Library/FrameBuffer.h
	includes/Core/GraphicsEngine/Library/IndexStaticBuffer.h
	includes/Core/GraphicsEngine/Library/VertexArrayBuffer.h
	includes/Core/GraphicsEngine/Library/VertexDynamicBuffer.h
	includes/Core/GraphicsEngine/Library/VertexStaticBuffer.h
	includes/Core/GraphicsEngine/Library/BufferLayout.h
	includes/Core/GraphicsEngine/Library/BufferElementType.h
	includes/Core/GraphicsEngine/Library/BufferElement.h
	includes/Core/GraphicsEngine/Library/Sprite.h
	includes/Core/GraphicsEngine/Library/Spritesheet.h
	includes/Core/GraphicsEngine/Library/FrameBufferData.h
	includes/Core/GraphicsEngine/Library/Renderer.h
	includes/Core/GraphicsEngine/Library/Renderer2D.h
	includes/Core/GraphicsEngine/Library/Camera.h

	includes/EventsSystem/Keyboard.h
	includes/EventsSystem/KeyboardEvent.h
	includes/EventsSystem/KeyboardEventType.h
	includes/EventsSystem/Mouse.h
	includes/EventsSystem/MouseEvent.h
	includes/EventsSystem/MouseEventType.h
	includes/EventsSystem/Window.h
	includes/EventsSystem/WindowEvent.h
	includes/EventsSystem/WindowEventType.h
	includes/EventsSystem/EventManager.h

	includes/ECS/Scene.h
	includes/ECS/Entity.h
	includes/ECS/ScriptableEntity.h

	includes/ECS/Components/Component.h
	includes/ECS/Components/TransformComponent.h
	includes/ECS/Components/ColorComponent.h
	includes/ECS/Components/TextureComponent.h
	includes/ECS/Components/SpriteComponent.h
	includes/ECS/Components/CameraComponent.h
	includes/ECS/Components/CppScriptComponent.h
	includes/ECS/Components/QuadComponent.h
	includes/ECS/Components/StateMachine2DAnimationComponent.h

	includes/Math/Vector.h
	includes/Math/Vector2.h
	includes/Math/Vector3.h
	includes/Math/Vector4.h
	
	includes/Memory/CacheStorage.h
	includes/Memory/TimedCache.h

	includes/Tools/Log.h
	includes/Tools/Layer.h
	includes/Tools/Time.h
	includes/Tools/LayerStack.h
)

set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES "")

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES
		src/Core/Platform/Browser/BrowserWindow.h
		src/Core/Platform/Windows/WindowsWindow.h
		src/Core/Platform/Glfw/GlfwWindow.h

		src/Core/GraphicsEngine/Library/WebGL/WebGLGraphicsLibrary.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLContext.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLShaderProgram.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLFrameBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexDynamicBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLRenderer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLTexture.h
		
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLGraphicsLibrary.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLContext.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLShaderProgram.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLFrameBuffer.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLVertexDynamicBuffer.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLRenderer.h
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLTexture.h
		
		#src/Core/GraphicsEngine/DirectX/DirectX11Context.h
		#src/Core/GraphicsEngine/DirectX/DirectX12Context.h
	)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	set(GAME_ENGINE_PRIVATE_PLATFORM_INCLUDES
		src/Core/Platform/Browser/BrowserWindow.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLGraphicsLibrary.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLContext.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLShaderProgram.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLFrameBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLIndexStaticBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexStaticBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexDynamicBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexArrayBuffer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLRenderer.h
		src/Core/GraphicsEngine/Library/WebGL/WebGLTexture.h
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

		src/Core/GraphicsEngine/Library/WebGL/WebGLGraphicsLibrary.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLContext.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLShaderProgram.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLRenderer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLTexture.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLFrameBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexDynamicBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexArrayBuffer.cpp

		src/Core/GraphicsEngine/Library/OpenGL/OpenGLGraphicsLibrary.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLContext.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLShaderProgram.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLRenderer.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLTexture.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLFrameBuffer.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLVertexDynamicBuffer.cpp
		src/Core/GraphicsEngine/Library/OpenGL/OpenGLVertexArrayBuffer.cpp
		
		#src/Core/GraphicsEngine/DirectX/DirectX11Context.cpp
		#src/Core/GraphicsEngine/DirectX/DirectX12Context.cpp	
	)
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
	set(GAME_ENGINE_PRIVATE_PLATFORM_SOURCES
		src/Core/Platform/Browser/BrowserWindow.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLGraphicsLibrary.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLContext.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLShaderProgram.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLFrameBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLIndexStaticBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexStaticBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexDynamicBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLVertexArrayBuffer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLRenderer.cpp
		src/Core/GraphicsEngine/Library/WebGL/WebGLTexture.cpp
	)
endif()

set(GAME_ENGINE_PRIVATE_SOURCES
	src/GameEngine.cpp

	src/Core/GraphicsEngine/Window.cpp
	src/Core/GraphicsEngine/WindowFactory.cpp
	src/Core/GraphicsEngine/GraphicsEngine.cpp

	src/Core/GraphicsEngine/Library/GraphicsLibrary.cpp
	src/Core/GraphicsEngine/Library/GraphicsLibraryFactory.cpp
	src/Core/GraphicsEngine/Library/GraphicsContext.cpp
	src/Core/GraphicsEngine/Library/RendererAPI.cpp
	src/Core/GraphicsEngine/Library/ShaderProgram.cpp
	src/Core/GraphicsEngine/Library/Texture.cpp
	src/Core/GraphicsEngine/Library/FrameBuffer.cpp
	src/Core/GraphicsEngine/Library/IndexStaticBuffer.cpp
	src/Core/GraphicsEngine/Library/VertexArrayBuffer.cpp
	src/Core/GraphicsEngine/Library/VertexDynamicBuffer.cpp
	src/Core/GraphicsEngine/Library/VertexStaticBuffer.cpp
	src/Core/GraphicsEngine/Library/BufferLayout.cpp
	src/Core/GraphicsEngine/Library/BufferElement.cpp
	src/Core/GraphicsEngine/Library/Sprite.cpp
	src/Core/GraphicsEngine/Library/Spritesheet.cpp
	src/Core/GraphicsEngine/Library/Renderer.cpp
	src/Core/GraphicsEngine/Library/Renderer2D.cpp
	src/Core/GraphicsEngine/Library/Camera.cpp

	${GAME_ENGINE_PRIVATE_PLATFORM_SOURCES}

	src/EventsSystem/Keyboard.cpp
	src/EventsSystem/KeyboardEvent.cpp
	src/EventsSystem/Mouse.cpp
	src/EventsSystem/MouseEvent.cpp
	src/EventsSystem/Window.cpp
	src/EventsSystem/WindowEvent.cpp
	src/EventsSystem/EventManager.cpp

	src/ECS/Scene.cpp
	src/ECS/Entity.cpp

	src/Math/Vector.cpp
	src/Math/Vector2.cpp
	src/Math/Vector3.cpp
	src/Math/Vector4.cpp

	src/Memory/CacheStorage.cpp
	src/Memory/TimedCache.cpp

	src/Tools/Log.cpp
	src/Tools/Layer.cpp
	src/Tools/Time.cpp
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

add_subdirectory(./vendor/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PUBLIC glm)

add_subdirectory(./vendor/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(./vendor/stb ${CMAKE_CURRENT_BINARY_DIR}/stb)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE stb)

add_subdirectory(./vendor/yaml ${CMAKE_CURRENT_BINARY_DIR}/yaml)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)

add_subdirectory(./vendor/entt ${CMAKE_CURRENT_BINARY_DIR}/entt)
target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PUBLIC EnTT)

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
	add_subdirectory(./vendor/sdl ${CMAKE_CURRENT_BINARY_DIR}/sdl)
	target_include_directories(${GAME_ENGINE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl/include)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE SDL2::SDL2)

	add_subdirectory(./vendor/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE glfw)
	
	target_link_libraries(${GAME_ENGINE_PROJECT_NAME} PRIVATE OpenGL32.lib)

	add_custom_command(TARGET ${GAME_ENGINE_PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2$<$<CONFIG:Debug>:d>.dll
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