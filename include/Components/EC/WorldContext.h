#pragma once
#include <Engine/NativeContext.h>
#include <EC/PositionEvent.h>

namespace Engine::Components
{
    struct WorldContext
    {
        NativeContext* native_context;
        PositionEvent::Bus* position_bus;
    };
}