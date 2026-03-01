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
        include/Engine/Engine/Input.h
        src/Engine/Log.cpp
        src/Engine/EntityId.cpp
        src/Engine/Entity.cpp
        src/Engine/Component.cpp
)
target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Engine
)