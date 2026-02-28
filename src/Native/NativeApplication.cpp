#include <Native/NativeApplication.h>

namespace Engine::Native {
    NativeApplication::NativeApplication() {
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow("Flappy Bird", 144 * scale, 256 * scale, 0);
        if (!window) {
            SDL_Log("Failed to create window: %s", SDL_GetError());
            throw NativeException("Failed to create window");
        }
        renderer = SDL_CreateRenderer(window, nullptr);
        if (!renderer) {
            SDL_Log("Failed to create renderer: %s", SDL_GetError());
            throw NativeException("Failed to create renderer");
        }

        SDL_SetRenderVSync(renderer, true);

        log_bus.subscribe(this);

        log = new Engine::Log(&log_bus);
        texture_loader = new Engine::Native::TextureLoader(renderer);
    }

    void NativeApplication::render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_bus.broadcast(&Engine::RenderEvent::on_render, static_cast<Engine::RenderBuffer*>(this));

        SDL_RenderPresent(renderer);
    }

    NativeApplication::~NativeApplication() {
        if (texture_loader) {
            delete texture_loader;
        }
        if (log) {
            delete log;
        }
        log_bus.unsubscribe(this);
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }

    Engine::NativeContext NativeApplication::make_context() {
        return Engine::NativeContext{
            .render_bus = &render_bus,
            .tick_bus = &ticker.get_bus(),
            .log = log,
            .texture_loader = texture_loader,
        };
    }

    void NativeApplication::run() {
        bool running = true;
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    running = false;
                }
            }
            ticker.tick();
            render();
        }
    }

    void NativeApplication::on_info(const std::string& message) {
        SDL_Log("[INFO] - %s", message.c_str());
    }

    void NativeApplication::draw_texture(const Engine::Texture* texture, const Engine::FRect& dest) {
        SDL_FRect sdl_dest = { dest.x * scale, dest.y * scale, dest.width * scale, dest.height * scale };
        SDL_RenderTexture(renderer, texture->impl->holder->texture, nullptr, &sdl_dest);
    }

    void NativeApplication::draw_texture(const Engine::Texture* texture, const Engine::FRect& dest, const Engine::FRect& src) {
        SDL_FRect sdl_dest = { dest.x * scale, dest.y * scale, dest.width * scale, dest.height * scale };
        SDL_FRect sdl_src = { src.x, src.y, src.width, src.height };
        SDL_RenderTexture(renderer, texture->impl->holder->texture, &sdl_src, &sdl_dest);
    }
}