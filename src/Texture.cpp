#include "Texture.hpp"


Texture::Texture() {
    this->guid = Util::generateGUID();
    this->textureID = 0;
    this->name = "";
    this->path = "";
    this->type = TEXTURE_ALBEDO;
    this->mode = GL_TEXTURE_2D;
    this->wrap_S = GL_REPEAT;
    this->wrap_T = GL_REPEAT;
    this->filterMin = GL_LINEAR_MIPMAP_LINEAR;
    this->filterMax = GL_LINEAR;
    this->format = GL_RGBA;
    this->width = 800;
    this->height = 600;
}

Texture::Texture(const std::string& name, const std::string& path, TextureType type) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->path = path;
    this->type = type;
    this->mode = GL_TEXTURE_2D;
    this->wrap_S = GL_REPEAT;
    this->wrap_T = GL_REPEAT;
    this->filterMin = GL_LINEAR_MIPMAP_LINEAR;
    this->filterMax = GL_LINEAR;
    glGenTextures(1, &this->textureID);
    int tempWidth, tempHeight, tempNumberOfChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(this->path.c_str(), &tempWidth, &tempHeight, &tempNumberOfChannels, 0);
    if (tempNumberOfChannels == 1) {
        this->format = GL_RED;
    }
    else if (tempNumberOfChannels == 2) {
        this->format = GL_RG;
    }
    else if (tempNumberOfChannels == 3) {
        this->format = GL_RGB;
    }
    else if (tempNumberOfChannels == 4) {
        this->format = GL_RGBA;
    }
    this->width = tempWidth;
    this->height = tempHeight;
    this->generate(data);
    stbi_image_free(data);
}

Texture::Texture(const std::string& path, TextureType type) {
    this->guid = Util::generateGUID();
    this->name = "";
    this->path = path;
    this->type = type;
    this->mode = GL_TEXTURE_2D;
    this->wrap_S = GL_REPEAT;
    this->wrap_T = GL_REPEAT;
    this->filterMin = GL_LINEAR_MIPMAP_LINEAR;
    this->filterMax = GL_LINEAR;
    int tempWidth, tempHeight, tempNumberOfChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(this->path.c_str(), &tempWidth, &tempHeight, &tempNumberOfChannels, 0);
    if (tempNumberOfChannels == 1) {
        this->format = GL_RED;
    }
    else if (tempNumberOfChannels == 2) {
        this->format = GL_RG;
    }
    else if (tempNumberOfChannels == 3) {
        this->format = GL_RGB;
    }
    else if (tempNumberOfChannels == 4) {
        this->format = GL_RGBA;
    }
    this->width = tempWidth;
    this->height = tempHeight;
    this->generate(data);
    stbi_image_free(data);
}

Texture::~Texture() {
}
void Texture::generate(unsigned char* data) {
    glGenTextures(1, &this->textureID);
    glBindTexture(this->mode, this->textureID);
    glTexImage2D(this->mode, 0, this->format, this->width, this->height, 0, this->format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(this->mode);
    glTexParameteri(this->mode, GL_TEXTURE_WRAP_S, this->wrap_S);
    glTexParameteri(this->mode, GL_TEXTURE_WRAP_T, this->wrap_T);
    glTexParameteri(this->mode, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(this->mode, GL_TEXTURE_MAG_FILTER, this->filterMax);
    unbind();
    
}
void Texture::bind(unsigned int textureChannel) {
    glActiveTexture(GL_TEXTURE0 + textureChannel);
    glBindTexture(this->mode, this->textureID);
}
void Texture::unbind() {
    glBindTexture(this->mode, 0);
}

TextureType Texture::assimpToRegularTextureType(aiTextureType aiTextureType) {
    if (aiTextureType == aiTextureType_BASE_COLOR) {
        return TEXTURE_ALBEDO;
    }
    if (aiTextureType == aiTextureType_DIFFUSE) {
        return TEXTURE_DIFFUSE;
    }
    if (aiTextureType == aiTextureType_SPECULAR) {
        return TEXTURE_SPECULAR;
    }
    if (aiTextureType == aiTextureType_NORMALS) {
        return TEXTURE_NORMAL;
    }
    if (aiTextureType == aiTextureType_HEIGHT) {
        return TEXTURE_HEIGHT;
    }
    if (aiTextureType == aiTextureType_DIFFUSE_ROUGHNESS) {
        return TEXTURE_ROUGHNESS;
    }
    if (aiTextureType == aiTextureType_SHININESS) {
        return TEXTURE_SHININESS;
    }
    if (aiTextureType == aiTextureType_METALNESS) {
        return TEXTURE_METALNESS;
    }
    if (aiTextureType == aiTextureType_AMBIENT_OCCLUSION) {
        return TEXTURE_AMBIENT_OCCLUSION;
    }
    return TEXTURE_ALBEDO;
}

aiTextureType Texture::regularToAssimpTextureType(TextureType textureType) {
    if (textureType == TEXTURE_ALBEDO) {
        return aiTextureType_BASE_COLOR;
    }
    if (textureType == TEXTURE_DIFFUSE) {
        return aiTextureType_DIFFUSE;
    }
    if (textureType == TEXTURE_SPECULAR) {
        return aiTextureType_SPECULAR;
    }
    if (textureType == TEXTURE_NORMAL) {
        return aiTextureType_NORMALS;
    }
    if (textureType == TEXTURE_HEIGHT) {
        return aiTextureType_HEIGHT;
    }
    if (textureType == TEXTURE_ROUGHNESS) {
        return aiTextureType_DIFFUSE_ROUGHNESS;
    }
    if (textureType == TEXTURE_SHININESS) {
        return aiTextureType_SHININESS;
    }
    if (textureType == TEXTURE_METALNESS) {
        return aiTextureType_METALNESS;
    }
    if (textureType == TEXTURE_AMBIENT_OCCLUSION) {
        return aiTextureType_AMBIENT_OCCLUSION;
    }
    return aiTextureType_BASE_COLOR;
}