#pragma once
#include <Engine/NativeContext.h>
#include <Engine/Log.h>
#include <Engine/Input.h>
#include <Native/Native.h>
#include <Native/Ticker.h>
#include <Native/ConsoleOpener.h>
#include <Native/LogWindow.h>


namespace Engine::Native {
    class NativeApplication : public NativeLogEvent, public RenderBuffer, public ConsoleOpener {
        SDL_Window* window;
        SDL_Renderer* renderer;

        LogWindow* log_window = nullptr;

        Engine::RenderEvent::Bus render_bus;
        Engine::NativeLogEvent::Bus log_bus;
        Engine::InputEvent::Bus input_bus;
        Engine::Log* log = nullptr;
        Engine::TextureLoader* texture_loader = nullptr;
        Ticker ticker;

        void render();

        int scale = 4;
        float num_delta_time = 0;
    public:
        NativeApplication();
        ~NativeApplication() override;

        NativeContext make_context();

        void run();

        void on_info(const std::string& message) override;
        void draw_texture(const Engine::Texture* texture, const Engine::FRect& dest) override;
        void draw_texture(const Engine::Texture* texture, const Engine::FRect& dest, const Engine::FRect& src) override;
        void open_console() override;
        void close_console() override;
        NativeLogEvent::Bus* get_log_bus() override;
    };
}
