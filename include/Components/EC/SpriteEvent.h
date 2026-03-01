#pragma once
#include <Engine/Types.h>
#include <Engine/Component.h>
#include <Engine/EventBus.h>

namespace Engine::Components {
    class SpriteEvent {
    public:
        using Bus = EventBus<SpriteEvent>;
        
        virtual void set_frame(int frame) = 0;
        virtual void get_frame(int& out_frame) const = 0;
    };
}