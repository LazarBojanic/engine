#include "DrawData.hpp"

DrawData::DrawData() {
    this->guid = Util::generateGUID();
    this->name = "";
    this->useTextureAlbedo = true;
    this->useTextureDiffuse = true;
    this->useTextureSpecular = true;
    this->useTextureNormal = true;
    this->useTextureHeight = false;
    this->useTextureRoughness = false;
    this->useTextureShininess = false;
    this->useTextureMetalness = false;
    this->useTextureAmbientOcclusion = false;
    this->shadingType = SHADING_TYPE::PHONG;
}

DrawData::DrawData(const std::string& name,
        std::shared_ptr<Mesh> mesh,
        std::shared_ptr<Material> material,
        std::shared_ptr<Texture> textureAlbedo,
        std::shared_ptr<Texture> textureDiffuse,
        std::shared_ptr<Texture> textureSpecular,
        std::shared_ptr<Texture> textureNormal,
        std::shared_ptr<Texture> textureHeight,
        std::shared_ptr<Texture> textureRoughness,
        std::shared_ptr<Texture> textureShininess,
        std::shared_ptr<Texture> textureMetalness,
        std::shared_ptr<Texture> textureAmbientOcclusion,
        std::shared_ptr<Shader> shaderPhong,
        std::shared_ptr<Shader> shaderPBR,
        bool useTextureAlbedo,
        bool useTextureDiffuse,
        bool useTextureSpecular,
        bool useTextureNormal,
        bool useTextureHeight,
        bool useTextureRoughness,
        bool useTextureShininess,
        bool useTextureMetalness,
        bool useTextureAmbientOcclusion,
        SHADING_TYPE shadingType) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->mesh = std::move(mesh);
    this->material = std::move(material);
    this->textureAlbedo = std::move(textureAlbedo);
    this->textureDiffuse = std::move(textureDiffuse);
    this->textureSpecular = std::move(textureSpecular);
    this->textureNormal = std::move(textureNormal);
    this->textureHeight = std::move(textureHeight);
    this->textureRoughness = std::move(textureRoughness);
    this->textureShininess = std::move(textureShininess);
    this->textureMetalness = std::move(textureMetalness);
    this->textureAmbientOcclusion = std::move(textureAmbientOcclusion);
    this->shaderPhong = std::move(shaderPhong);
    this->shaderPBR = std::move(shaderPBR);
    this->useTextureAlbedo = useTextureAlbedo;
    this->useTextureDiffuse = useTextureDiffuse;
    this->useTextureSpecular = useTextureSpecular;
    this->useTextureNormal = useTextureNormal;
    this->useTextureHeight = useTextureHeight;
    this->useTextureRoughness = useTextureRoughness;
    this->useTextureShininess = useTextureShininess;
    this->useTextureMetalness = useTextureMetalness;
    this->useTextureAmbientOcclusion = useTextureAmbientOcclusion;
    this->shadingType = shadingType;
}

DrawData::~DrawData() {
}
