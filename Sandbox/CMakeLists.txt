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
    set(USE_FLAGS "-s USE_SDL=2 -s FULL_ES3=1 -s USE_WEBGL2=1 -s USE_PTHREADS=1 -s ALLOW_MEMORY_GROWTH=1 -pthread --preload-file ${CMAKE_SOURCE_DIR}/${SANDBOX_PROJECT_NAME}/assets@/assets --use-preload-plugins -matomics -mbulk-memory")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    target_compile_definitions(GameEngine PUBLIC GAME_ENGINE_PLATFORM_BROWSER)
endif()

add_definitions(-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)