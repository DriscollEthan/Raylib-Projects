#ifndef RAYLIB_CPP_INCLUDE_TEXTURE_HPP_
#define RAYLIB_CPP_INCLUDE_TEXTURE_HPP_

#include "./TextureUnmanaged.hpp"

namespace raylib {
/**
 * Texture type
 *
 * The texture will be unloaded on object destruction. Use raylib::TextureUnmanaged if you're looking to not unload.
 *
 * @see raylib::TextureUnmanaged
 */
class Texture : public TextureUnmanaged {
public:
    using TextureUnmanaged::TextureUnmanaged;

    /**
     * Explicitly forbid the copy constructor.
     */
    Texture(const Texture& _other)
    {
        id = _other.id;
        width = _other.width;
        height = _other.height;
        mipmaps = _other.mipmaps;
        format = _other.format;
    }

    /**
     * Explicitly forbid copy assignment.
     */
    Texture& operator=(const Texture& _other)
    {
        id = _other.id;
        width = _other.width;
        height = _other.height;
        mipmaps = _other.mipmaps;
        format = _other.format;
        return *this;
    }

    Texture(int _id, int _width, int _height, int _mipmaps, int _format)
    {
        id = _id;
        width = _width;
        height = _height;
        mipmaps = _mipmaps;
        format = _format;
    }

    /**
     * Move constructor.
     */
    Texture(Texture&& other)  noexcept {
        set(other);

        other.id = 0;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;
    }

    /**
     * On destruction, unload the Texture.
     */
    ~Texture() { Unload(); }

    /**
     * Move assignment.
     */
    Texture& operator=(Texture&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;

        return *this;
    }
};

// Create the Texture aliases.
using Texture2D = Texture;
using TextureCubemap = Texture;

} // namespace raylib

using RTexture = raylib::Texture;
using RTexture2D = raylib::Texture2D;
using RTextureCubemap = raylib::TextureCubemap;

#endif // RAYLIB_CPP_INCLUDE_TEXTURE_HPP_
