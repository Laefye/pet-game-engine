#include <Native/Ticker.h>

namespace Engine::Native {
    TickEvent::Bus& Ticker::get_bus() {
        return tick_bus;
    }

    void Ticker::tick() {
        Uint64 current_time = SDL_GetPerformanceCounter();
        
        if (last_tick_time == 0) {
            last_tick_time = current_time;
        }
        
        delta_time = (current_time - last_tick_time) / static_cast<double>(SDL_GetPerformanceFrequency());
        last_tick_time = current_time;
        frame_count++;
        
        tick_bus.emit(&TickEvent::on_tick, static_cast<float>(delta_time));
    }

    Uint64 Ticker::get_frame_count() const {
        return frame_count;
    }

    double Ticker::get_delta_time() const {
        return delta_time;
    }
}
