#include <EC/Sprite.h>

namespace Engine::Components {
    Sprite::Sprite(const WithEntityId* entity_id, WorldContext* world_context, const SpriteDescription& description) :
    Component(entity_id), world_context(world_context), description(description),
    current_frame(0)
    {
        connect(this, world_context->get_sprite_bus());
        connect(this, world_context->native_context->render_bus);
    }

    Sprite::~Sprite() {
        disconnect(this, world_context->native_context->render_bus);
        disconnect(this, world_context->get_sprite_bus());
    }

    void Sprite::on_render(RenderBuffer* renderer) const {
        Vec2f position{};
        world_context->get_position_bus()->to_entity(get_entity_id(), &PositionEvent::get_position, position);
        const FRect src{description.width * static_cast<float>(current_frame), 0, description.width, description.height};
        const FRect dest{position.x, position.y, description.width, description.height};
        renderer->draw_texture(description.texture, dest, src);
    }

    void Sprite::set_frame(int frame) {
        current_frame = frame % description.frames;
    }

    void Sprite::get_frame(int& out_frame) const {
        out_frame = current_frame;
    }
}