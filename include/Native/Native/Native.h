#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <Engine/RenderSystem.h>
#include <exception>

namespace Engine::Native {
    class NativeException : public std::exception {
        std::string message;
    public:
        NativeException(const std::string& message) : message(message) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
    };

    struct TextureHolder {
        SDL_Texture* texture;
        TextureHolder(SDL_Texture* texture);
        TextureHolder(const TextureHolder& other) = delete;
        TextureHolder(TextureHolder&& other) = delete;
        ~TextureHolder();
    };
}

namespace Engine {
    struct Texture::Impl {
        std::shared_ptr<Native::TextureHolder> holder;
    };
}

namespace Engine::Native {
    struct Texture : public Engine::Texture {
        Texture(SDL_Texture* texture);
        Texture(const Texture& other);
        ~Texture();

        Engine::Texture* clone() const override;
    };
}
