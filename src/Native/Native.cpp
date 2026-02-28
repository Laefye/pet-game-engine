#include <Native/Native.h>

namespace Engine::Native {
    TextureHolder::TextureHolder(SDL_Texture* texture) : texture(texture) {}

    TextureHolder::~TextureHolder() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    Texture::Texture(SDL_Texture* texture) {
        impl = new Impl{ std::make_shared<TextureHolder>(texture) };
    }

    Texture::Texture(const Texture& other) {
        impl = new Impl{ other.impl->holder };
    }

    Texture::~Texture() {
        delete impl;
    }

    Engine::Texture* Texture::clone() const {
        return new Texture(*this);
    }
}
