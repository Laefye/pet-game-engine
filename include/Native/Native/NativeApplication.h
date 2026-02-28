#pragma once
#include <Engine/NativeContext.h>
#include <Engine/Log.h>
#include <Native/Native.h>
#include <Native/TextureLoader.h>
#include <Native/Ticker.h>

namespace Engine::Native {
    class NativeApplication : public Engine::NativeLogEvent, public Engine::RenderBuffer {
        SDL_Window* window;
        SDL_Renderer* renderer;

        Engine::RenderEvent::Bus render_bus;
        Engine::NativeLogEvent::Bus log_bus;
        Engine::Log* log = nullptr;
        Engine::TextureLoader* texture_loader = nullptr;
        Ticker ticker;

        void render();

        int scale = 4;
        float num_delta_time = 0;
    public:
        NativeApplication();
        ~NativeApplication();

        Engine::NativeContext make_context();

        void run();

        void on_info(const std::string& message) override;
        void draw_texture(const Engine::Texture* texture, const Engine::FRect& dest) override;
        void draw_texture(const Engine::Texture* texture, const Engine::FRect& dest, const Engine::FRect& src) override;
    };
}