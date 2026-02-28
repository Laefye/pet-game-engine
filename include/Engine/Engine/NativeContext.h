#pragma once
#include <Engine/RenderSystem.h>
#include <Engine/Log.h>
#include <Engine/Tick.h>

namespace Engine
{
    struct NativeContext
    {
        Engine::RenderEvent::Bus* render_bus;
        Engine::TickEvent::Bus* tick_bus;
        Engine::Log* log;
        Engine::TextureLoader* texture_loader;
    };
}