#pragma once
#include <Engine/Types.h>
#include <Engine/Component.h>
#include <Engine/EventBus.h>

namespace Engine::Components {
    class PositionEvent {
    public:
        using Bus = EventBus<PositionEvent>;
        
        virtual void get_position(Vec2f& out_position) const = 0;
        virtual void set_position(const Vec2f& position) = 0;
    };
}