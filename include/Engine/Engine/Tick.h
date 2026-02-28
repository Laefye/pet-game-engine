#pragma once
#include <Engine/EventBus.h>

namespace Engine {
    class TickEvent {
    public:
        using Bus = Engine::EventBus<TickEvent>;
        virtual ~TickEvent() = default;
        virtual void on_tick(float delta_time) = 0;
    };
}
