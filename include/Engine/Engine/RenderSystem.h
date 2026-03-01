#pragma once
#include <string>
#include <Engine/EventBus.h>
#include <Engine/Types.h>

namespace Engine
{
    struct Texture {
        struct Impl;
        Impl* impl;

        Texture() = default;
        Texture(const Texture& other) = delete;
        Texture(Texture&& other) = delete;
        
        virtual ~Texture() = default;
        virtual Texture* clone() const = 0;    
    };

    class TextureLoader {
    public:
        virtual ~TextureLoader() = default;

        virtual Texture* load_texture(const std::string& path) = 0;
    };

    class RenderBuffer {
    public:
        virtual ~RenderBuffer() = default;

        virtual void draw_texture(const Texture* texture, const FRect& dest) = 0;
        virtual void draw_texture(const Texture* texture, const FRect& dest, const FRect& src) = 0;
    };

    class RenderEvent
    {
    public:
        virtual ~RenderEvent() = default;

        using Bus = Engine::EventBus<RenderEvent>;

        virtual void on_render(RenderBuffer* renderer) const = 0;
    };
}