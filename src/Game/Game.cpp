#include <Game/Game.h>
#include <EC/Sprite.h>

namespace Game
{
    Game::Game(Engine::NativeContext context) : context(context)
    {
        context.render_bus->subscribe(this);
        context.tick_bus->subscribe(this);
        context.input_bus->subscribe(this);
        background = context.texture_loader->load_texture("assets/background.png");
        if (!background) {
            context.log->info("Failed to load background texture");
        }
        context.log->info("Loaded background texture");
        bird = context.texture_loader->load_texture("assets/bird.png");
        if (!bird) {
            context.log->info("Failed to load bird texture");
        }
        context.log->info("Loaded bird texture");

        world_context = new Engine::Components::WorldContext(&this->context);

        Engine::Components::SpriteDescription bird_description = {
            .width = 32,
            .height = 32,
            .frames = 3,
            .texture = bird
        };

        bird_entity = new Engine::Entity(0);
        context.log->info("Creating bird entity with ID: " + std::to_string(bird_entity->get_entity_id()));
        bird_entity->new_component<Engine::Components::Position>(world_context, 50.0f, 100.0f);
        bird_entity->new_component<Engine::Components::Sprite>(world_context, bird_description);
    }

    Game::~Game()
    {
        delete bird_entity;
        delete world_context;

        delete background;
        delete bird;

        context.input_bus->unsubscribe(this);
        context.tick_bus->unsubscribe(this);
        context.render_bus->unsubscribe(this);
    }

    void Game::on_render(Engine::RenderBuffer* renderer) const
    {
        renderer->draw_texture(background, { 0, 0, 144, 256 });
    }

    void Game::on_tick(float delta_time)
    {
        Engine::Vec2f position = {};
        world_context->get_position_bus()->to_entity(bird_entity->get_entity_id(), &Engine::Components::PositionEvent::get_position, position);
        position.y += 100.0f * delta_time;
        world_context->get_position_bus()->to_entity(bird_entity->get_entity_id(), &Engine::Components::PositionEvent::set_position, position);
    }

    void Game::on_key_down(Engine::Key key)
    {
        if (key == Engine::Key::Space) {
            Engine::Vec2f position{};
            world_context->get_position_bus()->to_entity(bird_entity->get_entity_id(), &Engine::Components::PositionEvent::get_position, position);
            position.y -= 50;
            world_context->get_position_bus()->to_entity(bird_entity->get_entity_id(), &Engine::Components::PositionEvent::set_position, position);
            context.log->info("Bird jumped!");
        }
    }
}