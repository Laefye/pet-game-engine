cmake_minimum_required(VERSION 3.10.0)
project(FlappyBird VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

set(CMAKE_CXX_STANDARD 23)

# Base Engine Library
add_library(Engine STATIC 
    include/Engine/Engine/EventBus.h
    include/Engine/Engine/RenderSystem.h
    include/Engine/Engine/Log.h
    include/Engine/Engine/EntityId.h
    include/Engine/Engine/Entity.h
    include/Engine/Engine/Tick.h
    include/Engine/Engine/Types.h
    include/Engine/Engine/NativeContext.h
    include/Engine/Engine/Component.h
    src/Engine/Log.cpp
    src/Engine/EntityId.cpp
    src/Engine/Entity.cpp
    src/Engine/Component.cpp
)
target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Engine
)

# Default Components
add_library(EC STATIC 
    include/Components/EC/PositionEvent.h
    include/Components/EC/Position.h
    include/Components/EC/Sprite.h
    include/Components/EC/WorldContext.h
    src/EC/Position.cpp
    src/EC/Sprite.cpp
)
target_include_directories(EC PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Components
)
target_link_libraries(EC PUBLIC Engine)

# Game Library
add_library(Game STATIC src/Game/Game.cpp)
target_include_directories(Game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Game
)
target_link_libraries(Game PUBLIC Engine EC)

# Native Application
add_executable(FlappyBird 
    include/Engine/Engine/Tick.h
    include/Native/Native/Native.h
    include/Native/Native/TextureLoader.h
    include/Native/Native/NativeApplication.h
    include/Native/Native/Ticker.h
    src/Native/main.cpp
    src/Native/Native.cpp
    src/Native/TextureLoader.cpp
    src/Native/NativeApplication.cpp
    src/Native/Ticker.cpp
)
target_include_directories(FlappyBird PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Native
)
target_link_libraries(FlappyBird PRIVATE SDL3::SDL3 SDL3_image::SDL3_image Engine Game EC)


if (WIN32)
    add_custom_command(TARGET FlappyBird POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:FlappyBird>
            $<TARGET_FILE_DIR:FlappyBird>
        COMMAND_EXPAND_LISTS
    )
endif(WIN32)

# Copy assets to build directory
add_custom_command(TARGET FlappyBird POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:FlappyBird>/assets
    COMMENT "Copying assets to build directory"
)
