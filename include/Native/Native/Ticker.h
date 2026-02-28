#pragma once
#include <SDL3/SDL.h>
#include <Engine/Tick.h>
#include <Native/Native.h>

namespace Engine::Native {
    class Ticker {
        TickEvent::Bus tick_bus;
        Uint64 frame_count = 0;
        double delta_time = 0.0;
        Uint64 last_tick_time = 0;

    public:
        Ticker() = default;
        ~Ticker() = default;

        void tick();
        
        Uint64 get_frame_count() const;
        double get_delta_time() const;

        TickEvent::Bus& get_bus();
    };
}
