find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON)

add_executable(FlappyBird
        include/Engine/Engine/Tick.h
        include/Native/Native/Native.h
        include/Native/Native/TextureLoader.h
        include/Native/Native/NativeApplication.h
        include/Native/Native/Ticker.h
        include/Native/Native/LogWindow.h
        src/Native/main.cpp
        src/Native/Native.cpp
        src/Native/TextureLoader.cpp
        src/Native/NativeApplication.cpp
        src/Native/Ticker.cpp
        src/Native/LogWindow.cpp
        include/Native/Native/ConsoleOpener.h
)
target_include_directories(FlappyBird PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Native
)
target_link_libraries(FlappyBird PRIVATE SDL3::SDL3 SDL3_image::SDL3_image Qt6::Core Qt6::Gui Qt6::Widgets Engine Game EC)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (WIN32)
        set_target_properties(FlappyBird PROPERTIES
                LINK_FLAGS "-mwindows"
        )
    endif(WIN32)
endif()

if (WIN32)
    add_custom_command(TARGET FlappyBird POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:FlappyBird>
            $<TARGET_FILE_DIR:FlappyBird>
            COMMAND_EXPAND_LISTS
    )
endif(WIN32)