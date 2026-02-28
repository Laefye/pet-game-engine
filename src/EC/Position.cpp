#include <EC/Position.h>

namespace Engine::Components {
    Position::Position(const WithEntityId* entity_id, WorldContext* world_context, float x, float y) : Component(entity_id), world_context(world_context), position{x, y} {
        connect(this, world_context->position_bus);
    }

    Position::~Position() {
        disconnect(this, world_context->position_bus);
    }

    void Position::get_position(Vec2f& out_position) const {
        out_position = position;
    }

    void Position::set_position(const Vec2f& position) {
        this->position = position;
    }
}
