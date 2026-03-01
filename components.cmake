add_library(EC STATIC
        include/Components/EC/PositionEvent.h
        include/Components/EC/Position.h
        include/Components/EC/SpriteEvent.h
        include/Components/EC/Sprite.h
        include/Components/EC/WorldContext.h
        src/EC/Position.cpp
        src/EC/Sprite.cpp
        src/EC/WorldContext.cpp
)
target_include_directories(EC PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Components
)
target_link_libraries(EC PUBLIC Engine)