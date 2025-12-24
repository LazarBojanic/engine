#pragma once
#include <string>

class TextureType {
    public:
    int index;
    std::string name;
    TextureType();
    TextureType(int index, const std::string& name);
    ~TextureType();

    bool operator==(const TextureType& other) const {
        return index == other.index && name == other.name;
    }

    bool operator!=(const TextureType& other) const {
        return !(*this == other);
    }

};

inline const auto TEXTURE_ALBEDO = TextureType(0, "textureAlbedo");
inline const auto TEXTURE_DIFFUSE = TextureType(1, "textureDiffuse");
inline  auto TEXTURE_SPECULAR = TextureType(2, "textureSpecular");
inline const auto TEXTURE_NORMAL = TextureType(3, "textureNormal");
inline const auto TEXTURE_HEIGHT = TextureType(4, "textureHeight");
inline  auto TEXTURE_ROUGHNESS = TextureType(5, "textureRoughness");
inline const auto TEXTURE_SHININESS = TextureType(6, "textureShininess");
inline const auto TEXTURE_METALNESS = TextureType(7, "textureMetalness");
inline const auto TEXTURE_AMBIENT_OCCLUSION = TextureType(8, "textureAmbientOcclusion");
