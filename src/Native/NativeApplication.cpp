#include <Native/NativeApplication.h>
#include <Native/TextureLoader.h>

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

        log = new Log(&log_bus);
        texture_loader = new TextureLoader(renderer);
    }

    void NativeApplication::render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_bus.broadcast(&Engine::RenderEvent::on_render, static_cast<Engine::RenderBuffer*>(this));

        SDL_RenderPresent(renderer);
    }

    NativeApplication::~NativeApplication() {
        delete texture_loader;
        delete log;

        log_bus.unsubscribe(this);
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }

    NativeContext NativeApplication::make_context() {
        return NativeContext{
            .render_bus = &render_bus,
            .tick_bus = &ticker.get_bus(),
            .input_bus = &input_bus,
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
                else if (event.type == SDL_EVENT_KEY_DOWN) {
                    switch (event.key.key) {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_SPACE:
                            input_bus.broadcast(&InputEvent::on_key_down, Space);
                            break;
                        case SDLK_GRAVE:
                            open_console();
                            break;
                        default:
                            break;
                    }
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

    void NativeApplication::open_console() {
        if (!log_window) {
            log_window = new LogWindow(nullptr, this);
            log_window->show();
        }
    }

    void NativeApplication::close_console() {
        if (log_window) {
            log_window->close();
            delete log_window;
            log_window = nullptr;
        }
    }

    NativeLogEvent::Bus* NativeApplication::get_log_bus() {
        return &log_bus;
    }
}
