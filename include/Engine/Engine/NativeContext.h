#pragma once
#include <Engine/RenderSystem.h>
#include <Engine/Log.h>
#include <Engine/Tick.h>

#include "Input.h"

namespace Engine
{
    struct NativeContext
    {
        RenderEvent::Bus* render_bus;
        TickEvent::Bus* tick_bus;
        InputEvent::Bus* input_bus;
        
        Log* log;
        TextureLoader* texture_loader;
    };
}
