cmake_minimum_required(VERSION 3.10.0)
project(FlappyBird VERSION 0.1.0 LANGUAGES C CXX)



set(CMAKE_CXX_STANDARD 23)

include(engine.cmake)
include(components.cmake)

# Game Library
add_library(Game STATIC src/Game/Game.cpp)
target_include_directories(Game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Game
)
target_link_libraries(Game PUBLIC Engine EC)

include(native.cmake)

# Copy assets to build directory
add_custom_command(TARGET FlappyBird POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:FlappyBird>/assets
    COMMENT "Copying assets to build directory"
)
