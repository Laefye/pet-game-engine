#pragma once
#include <Engine/RenderSystem.h>
#include <Engine/NativeContext.h>
#include <Engine/Entity.h>
#include <Engine/Input.h>
#include <EC/Position.h>
#include <EC/WorldContext.h>


namespace Game
{
    class Game :
        public Engine::RenderEvent,
        public Engine::TickEvent,
        public Engine::InputEvent
    {
        Engine::NativeContext context;
        Engine::Components::WorldContext* world_context;
        Engine::Texture* background = nullptr;
        Engine::Texture* bird = nullptr;
        float offset = 0;

        Engine::Entity* bird_entity;
    public:
        Game(Engine::NativeContext native_context);
        ~Game() override;

        void on_render(Engine::RenderBuffer* renderer) const override;
        void on_tick(float delta_time) override;
        void on_key_down(Engine::Key key) override;
    };
}