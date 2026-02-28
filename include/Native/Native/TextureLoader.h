#pragma once
#include <Native/Native.h>
#include <Engine/RenderSystem.h>

namespace Engine::Native {
    class TextureLoader : public Engine::TextureLoader {
        SDL_Renderer* renderer;
    public:
        TextureLoader(SDL_Renderer* renderer);

        Engine::Texture* load_texture(const std::string& path) override;
    };
}