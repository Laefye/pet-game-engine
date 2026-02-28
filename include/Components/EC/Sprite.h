#pragma once
#include <Engine/Component.h>
#include <Engine/RenderSystem.h>
#include <EC/Position.h>

namespace Engine::Components {
    class Sprite : public Component, public RenderEvent {
        WorldContext* world_context;
        const Texture* texture;
    public:
        Sprite(const WithEntityId* entity_id, WorldContext* world_context, const Texture* texture);
        ~Sprite();

        void on_render(RenderBuffer* renderer) const;
    };
}