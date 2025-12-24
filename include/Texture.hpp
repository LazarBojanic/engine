#pragma once

#include "TextureType.hpp"
#include "assimp/material.h"
#include "Util.hpp"
#include "stb/stb_image.h"

class Texture{
private:
	std::string guid;
	std::filesystem::path path;
    std::string name;
	TextureType type;
	unsigned int mode;
	unsigned int textureID;
	unsigned int width;
	unsigned int height;
    unsigned int wrap_S;
    unsigned int wrap_T;
    unsigned int filterMin;
    unsigned int filterMax;
    GLenum format;
public:

    Texture();
	Texture(const std::string& path, TextureType type);
    Texture(const std::string& name, const std::string& path, TextureType type);
    ~Texture();
    void generate(unsigned char* data);
    void bind(unsigned int textureChannel);
    void unbind();
	static TextureType assimpToRegularTextureType(aiTextureType aiTextureType);
	static aiTextureType regularToAssimpTextureType(TextureType textureType);
	const std::string& getGUID() {
		return this->guid;
	}
	std::filesystem::path getPath() {
		return this->path;
	}
	const std::string& getName() {
		return this->name;
	}
	unsigned int getMode() {
		return this->mode;
	}
	unsigned int getTextureID() {
		return this->textureID;
	}
	unsigned int getWidth() {
		return this->width;
	}
	unsigned int getHeight() {
		return this->height;
	}
	unsigned int getWrap_S() {
		return this->wrap_S;
	}
	unsigned int getWrap_T() {
		return this->wrap_T;
	}
	unsigned int getFilterMin() {
		return this->filterMin;
	}
	unsigned int getFilterMax() {
		return this->filterMax;
	}
	GLenum getFormat() {
		return this->format;
	}
	TextureType getType() {
		return this->type;
	}
	void setName(const std::string& name) {
		this->name = name;
	}
};