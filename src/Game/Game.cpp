#include <Game/Game.h>
#include <EC/Sprite.h>

namespace Game
{
    Game::Game(Engine::NativeContext context) : context(context)
    {
        context.render_bus->subscribe(this);
        background = context.texture_loader->load_texture("assets/background.png");
        if (!background) {
            context.log->info("Failed to load background texture");
        }
        bird = context.texture_loader->load_texture("assets/bird.png");
        if (!bird) {
            context.log->info("Failed to load bird texture");
        }
        context.tick_bus->subscribe(this);

        world_context.native_context = &context;
        world_context.position_bus = new Engine::Components::PositionEvent::Bus();

        bird_entity = new Engine::Entity(0);
        bird_entity->new_component<Engine::Components::Position>(&world_context, 100.0f, 100.0f);
        bird_entity->new_component<Engine::Components::Sprite>(&world_context, bird);
    }

    Game::~Game()
    {
        delete bird_entity;
        delete world_context.position_bus;
        if (background) {
            delete background;
        }
        if (bird) {
            delete bird;
        }
        context.tick_bus->unsubscribe(this);
        context.render_bus->unsubscribe(this);
    }

    void Game::on_render(Engine::RenderBuffer* renderer) const
    {
        renderer->draw_texture(background, { 0, 0, 144, 256 });
    }

    void Game::on_tick(float delta_time)
    {
        const Engine::Vec2f position = {50, 0 + offset};
        world_context.position_bus->to_entity(bird_entity->get_entity_id(), &Engine::Components::PositionEvent::set_position, position);
        offset += delta_time * 50;
    }
}