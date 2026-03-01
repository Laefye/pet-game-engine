#include <EC/WorldContext.h>

namespace Engine::Components
{
    WorldContext::WorldContext(NativeContext* context) : native_context(context) {
    }

    PositionEvent::Bus* WorldContext::get_position_bus() {
        return &position_bus;
    }

    SpriteEvent::Bus* WorldContext::get_sprite_bus() {
        return &sprite_bus;
    }
}