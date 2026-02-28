#pragma once
#include <Engine/Types.h>
#include <Engine/Component.h>
#include <Engine/EventBus.h>
#include <EC/PositionEvent.h>
#include <EC/WorldContext.h>

namespace Engine::Components {
    class Position : public Component, public PositionEvent {
        Vec2f position;
        WorldContext* world_context;
    public:
        Position(const WithEntityId* entity_id, WorldContext* world_context, float x, float y);
        ~Position();
        
        void get_position(Vec2f& out_position) const override;
        void set_position(const Vec2f& position) override;
    };
}