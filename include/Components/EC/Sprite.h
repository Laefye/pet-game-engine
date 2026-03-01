#pragma once
#include <Engine/Component.h>
#include <Engine/RenderSystem.h>
#include <EC/Position.h>
#include <EC/SpriteEvent.h>
#include <vector>

namespace Engine::Components {
    struct SpriteDescription {
        float width;
        float height;
        int frames;
        const Texture* texture;
    };

    class Sprite : public Component, public RenderEvent, public SpriteEvent
    {
        WorldContext* world_context;
        SpriteDescription description;
        int current_frame;
    public:
        Sprite(const WithEntityId* entity_id, WorldContext* world_context, const SpriteDescription& description);
        ~Sprite();

        void on_render(RenderBuffer* renderer) const;
        void set_frame(int frame) override;
        void get_frame(int& out_frame) const override;
    };
}