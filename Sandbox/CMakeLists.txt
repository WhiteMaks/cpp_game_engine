cmake_minimum_required(VERSION 3.22)

set(SANDBOX_PROJECT_NAME Sandbox)

set(SANDBOX_SOURCES
	src/Sandbox.cpp

	src/Layers/TestLayer.cpp

	src/Renderer/FixedFullScreenTextureRenderer.cpp

    src/Scripts/CameraController.cpp
    src/Scripts/Rotation.cpp
)

set(SANDBOX_INCLUDES
    includes/Layers/TestLayer.h

    includes/Renderer/FixedFullScreenTextureRenderer.h

    includes/Scripts/CameraController.h
    includes/Scripts/Rotation.h
)

set(SANDBOX_TEXTURES

)

set(SANDBOX_SPRITESHEETS
    assets/spritesheets/tiny_town_16x16_0x0.png
    assets/spritesheets/character_spritesheet.png
    assets/spritesheets/decoration_and_block_spritesheet.png
    assets/spritesheets/item_spritesheet.png
)

set(SANDBOX_SHADERS
    assets/shaders/texture_shader_opengl.glsl
    assets/shaders/texture_shader_webgl.glsl

    assets/shaders/color_shader_opengl.glsl
    assets/shaders/color_shader_webgl.glsl

    assets/shaders/default_2d_shader_opengl.glsl
    assets/shaders/default_2d_shader_webgl.glsl

    assets/shaders/fixed_full_screen_texture_shader_opengl.glsl
    assets/shaders/fixed_full_screen_texture_shader_webgl.glsl
)

set(SANDBOX_ALL_SOURCES
	${SANDBOX_SOURCES}
	${SANDBOX_INCLUDES}
	${SANDBOX_TEXTURES}
	${SANDBOX_SPRITESHEETS}
	${SANDBOX_SHADERS}
)

add_executable(${SANDBOX_PROJECT_NAME}
	${SANDBOX_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${SANDBOX_ALL_SOURCES}
)

target_include_directories(${SANDBOX_PROJECT_NAME} PRIVATE src)
target_include_directories(${SANDBOX_PROJECT_NAME} PUBLIC includes)
target_include_directories(${SANDBOX_PROJECT_NAME} PRIVATE assets)

target_link_libraries(${SANDBOX_PROJECT_NAME} 
	GameEngine
)

target_compile_features(${SANDBOX_PROJECT_NAME} PUBLIC cxx_std_20)

set_target_properties(${SANDBOX_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set_target_properties(${SANDBOX_PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${SANDBOX_PROJECT_NAME}>)

message(STATUS "GAME_ENGINE_PLATFORM = " $ENV{GAME_ENGINE_PLATFORM})

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "WINDOWS")
    target_compile_definitions(GameEngine PUBLIC GAME_ENGINE_PLATFORM_WINDOWS)

    add_custom_command(TARGET ${SANDBOX_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${SANDBOX_PROJECT_NAME}/assets/
        $<TARGET_FILE_DIR:${SANDBOX_PROJECT_NAME}>/assets/
    )
endif()

if($ENV{GAME_ENGINE_PLATFORM} MATCHES "BROWSER")
    set(USE_FLAGS "-s USE_SDL=2 -s FULL_ES3=1 -s USE_WEBGL2=1 -s USE_PTHREADS=1 -s ALLOW_MEMORY_GROWTH=1 -pthread --preload-file ${CMAKE_SOURCE_DIR}/${SANDBOX_PROJECT_NAME}/assets@/assets --use-preload-plugins -matomics -mbulk-memory -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    target_compile_definitions(GameEngine PUBLIC GAME_ENGINE_PLATFORM_BROWSER)
endif()