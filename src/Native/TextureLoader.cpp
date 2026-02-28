#include <Native/TextureLoader.h>
#include <SDL3_image/SDL_image.h>

namespace Engine::Native {
    TextureLoader::TextureLoader(SDL_Renderer* renderer) : renderer(renderer) {}

    Engine::Texture* TextureLoader::load_texture(const std::string& path) {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface) {
            return nullptr;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        return new Texture(texture);
    }
}