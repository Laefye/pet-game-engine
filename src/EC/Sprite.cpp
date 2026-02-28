#include <EC/Sprite.h>

namespace Engine::Components {
    Sprite::Sprite(const WithEntityId* entity_id, WorldContext* world_context, const Texture* texture) : Component(entity_id), world_context(world_context), texture(texture) {
        connect(this, world_context->native_context->render_bus);
    }

    Sprite::~Sprite() {
        disconnect(this, world_context->native_context->render_bus);
    }

    void Sprite::on_render(RenderBuffer* renderer) const {
        Vec2f position;
        world_context->position_bus->to_entity(get_entity_id(), &PositionEvent::get_position, position);
        FRect dest{position.x, position.y, 32, 32};
        renderer->draw_texture(texture, dest);
    }
}