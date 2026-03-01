#pragma once
#include <Engine/NativeContext.h>
#include <EC/SpriteEvent.h>
#include <EC/PositionEvent.h>

namespace Engine::Components
{
    struct WorldContext
    {
        NativeContext* native_context;
        explicit WorldContext(NativeContext* context);
    private:
        PositionEvent::Bus position_bus;
        SpriteEvent::Bus sprite_bus;
    public:
        PositionEvent::Bus* get_position_bus();
        SpriteEvent::Bus* get_sprite_bus();
    };
}