#include "DrawData.hpp"

DrawData::DrawData() {
    this->guid = Util::generateGUID();
    this->name = "";
    this->mesh = std::make_shared<Mesh>();
    this->material = std::make_shared<Material>();
    this->guid = Util::generateGUID();
    this->name = "";
    this->mesh = std::make_shared<Mesh>();
    this->material = std::make_shared<Material>();
    this->textureAlbedo = std::make_shared<Texture>();
    this->textureDiffuse = std::make_shared<Texture>();
    this->textureSpecular = std::make_shared<Texture>();
    this->textureNormal = std::make_shared<Texture>();
    this->textureHeight = std::make_shared<Texture>();
    this->textureRoughness = std::make_shared<Texture>();
    this->textureShininess = std::make_shared<Texture>();
    this->textureMetalness = std::make_shared<Texture>();
    this->textureAmbientOcclusion = std::make_shared<Texture>();
    this->shaderPhong = std::make_shared<Shader>();
    this->shaderPBR = std::make_shared<Shader>();
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
    this->updateShaderTextures();
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
    this->mesh = mesh;
    this->material = material;
    this->textureAlbedo = textureAlbedo;
    this->textureDiffuse = textureDiffuse;
    this->textureSpecular = textureSpecular;
    this->textureNormal = textureNormal;
    this->textureHeight = textureHeight;
    this->textureRoughness = textureRoughness;
    this->textureShininess = textureShininess;
    this->textureMetalness = textureMetalness;
    this->textureAmbientOcclusion = textureAmbientOcclusion;
    this->shaderPhong = shaderPhong;
    this->shaderPBR = shaderPBR;
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
    this->updateShaderTextures();
}

DrawData::~DrawData() {
}

void DrawData::updateShaderTextures() {
    this->shaderPhong->setBool("useTextureAlbedo", this->useTextureAlbedo);
    this->shaderPhong->setInt(TEXTURE_ALBEDO.name, TEXTURE_ALBEDO.index);
    this->shaderPhong->setBool("useTextureDiffuse", this->useTextureDiffuse);
    this->shaderPhong->setInt(TEXTURE_DIFFUSE.name, TEXTURE_DIFFUSE.index);
    this->shaderPhong->setBool("useTextureSpecular", this->useTextureSpecular);
    this->shaderPhong->setInt(TEXTURE_SPECULAR.name, TEXTURE_SPECULAR.index);
    this->shaderPhong->setBool("useTextureNormal", this->useTextureNormal);
    this->shaderPhong->setInt(TEXTURE_NORMAL.name, TEXTURE_NORMAL.index);
    this->shaderPhong->setBool("useTextureHeight", this->useTextureHeight);
    this->shaderPhong->setInt(TEXTURE_HEIGHT.name, TEXTURE_HEIGHT.index);
    this->shaderPhong->setBool("useTextureRoughness", this->useTextureRoughness);
    this->shaderPhong->setInt(TEXTURE_ROUGHNESS.name, TEXTURE_ROUGHNESS.index);
    this->shaderPhong->setBool("useTextureShininess", this->useTextureShininess);
    this->shaderPhong->setInt(TEXTURE_SHININESS.name, TEXTURE_SHININESS.index);
    this->shaderPhong->setBool("useTextureMetalness", this->useTextureMetalness);
    this->shaderPhong->setInt(TEXTURE_METALNESS.name, TEXTURE_METALNESS.index);
    this->shaderPhong->setBool("useTextureAmbientOcclusion", this->useTextureAmbientOcclusion);
    this->shaderPhong->setInt(TEXTURE_AMBIENT_OCCLUSION.name, TEXTURE_AMBIENT_OCCLUSION.index);

    this->shaderPBR->setBool("useTextureAlbedo", this->useTextureAlbedo);
    this->shaderPBR->setInt(TEXTURE_ALBEDO.name, TEXTURE_ALBEDO.index);
    this->shaderPBR->setBool("useTextureDiffuse", this->useTextureDiffuse);
    this->shaderPBR->setInt(TEXTURE_DIFFUSE.name, TEXTURE_DIFFUSE.index);
    this->shaderPBR->setBool("useTextureSpecular", this->useTextureSpecular);
    this->shaderPBR->setInt(TEXTURE_SPECULAR.name, TEXTURE_SPECULAR.index);
    this->shaderPBR->setBool("useTextureNormal", this->useTextureNormal);
    this->shaderPBR->setInt(TEXTURE_NORMAL.name, TEXTURE_NORMAL.index);
    this->shaderPBR->setBool("useTextureHeight", this->useTextureHeight);
    this->shaderPBR->setInt(TEXTURE_HEIGHT.name, TEXTURE_HEIGHT.index);
    this->shaderPBR->setBool("useTextureRoughness", this->useTextureRoughness);
    this->shaderPBR->setInt(TEXTURE_ROUGHNESS.name, TEXTURE_ROUGHNESS.index);
    this->shaderPBR->setBool("useTextureShininess", this->useTextureShininess);
    this->shaderPBR->setInt(TEXTURE_SHININESS.name, TEXTURE_SHININESS.index);
    this->shaderPBR->setBool("useTextureMetalness", this->useTextureMetalness);
    this->shaderPBR->setInt(TEXTURE_METALNESS.name, TEXTURE_METALNESS.index);
    this->shaderPBR->setBool("useTextureAmbientOcclusion", this->useTextureAmbientOcclusion);
    this->shaderPBR->setInt(TEXTURE_AMBIENT_OCCLUSION.name, TEXTURE_AMBIENT_OCCLUSION.index);
}

