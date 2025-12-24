#pragma once

#include "Util.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

class DrawData {
private:
	std::string guid;
	std::string name;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
	std::shared_ptr<Texture> textureAlbedo;
	std::shared_ptr<Texture> textureDiffuse;
	std::shared_ptr<Texture> textureSpecular;
	std::shared_ptr<Texture> textureNormal;
	std::shared_ptr<Texture> textureHeight;
	std::shared_ptr<Texture> textureRoughness;
	std::shared_ptr<Texture> textureShininess;
	std::shared_ptr<Texture> textureMetalness;
	std::shared_ptr<Texture> textureAmbientOcclusion;
	std::shared_ptr<Shader> shaderPhong;
	std::shared_ptr<Shader> shaderPBR;
	bool useTextureAlbedo;
	bool useTextureDiffuse;
	bool useTextureSpecular;
	bool useTextureNormal;
	bool useTextureHeight;
	bool useTextureRoughness;
	bool useTextureShininess;
	bool useTextureMetalness;
	bool useTextureAmbientOcclusion;
	SHADING_TYPE shadingType;

public:
	DrawData();
	DrawData(const std::string& name,
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
		SHADING_TYPE shadingType);
	~DrawData();
	void updateShaderTextures();
	const std::string& getGUID() {
		return this->guid;
	}

	const std::string& getName() {
		return this->name;
	}

	std::shared_ptr<Mesh> getMesh() {
		return this->mesh;
	}

	std::shared_ptr<Material> getMaterial() {
		return this->material;
	}

	std::shared_ptr<Texture> getTextureAlbedo() {
		return this->textureAlbedo;
	}

	void setTextureAlbedo(const std::shared_ptr<Texture>& textureAlbedo) {
		this->textureAlbedo = textureAlbedo;
	}

	std::shared_ptr<Texture> getTextureDiffuse() {
		return this->textureDiffuse;
	}

	void setTextureDiffuse(const std::shared_ptr<Texture>& textureDiffuse) {
		this->textureDiffuse = textureDiffuse;
	}

	std::shared_ptr<Texture> getTextureSpecular() {
		return this->textureSpecular;
	}

	void setTextureSpecular(const std::shared_ptr<Texture>& textureSpecular) {
		this->textureSpecular = textureSpecular;
	}

	std::shared_ptr<Texture> getTextureNormal() {
		return this->textureNormal;
	}

	void setTextureNormal(const std::shared_ptr<Texture>& textureNormal) {
		this->textureNormal = textureNormal;
	}

	std::shared_ptr<Texture> getTextureHeight() {
		return this->textureHeight;
	}

	void setTextureHeight(const std::shared_ptr<Texture>& textureHeight) {
		this->textureHeight = textureHeight;
	}

	std::shared_ptr<Texture> getTextureRoughness() {
		return this->textureRoughness;
	}

	void setTextureRoughness(const std::shared_ptr<Texture>& textureRoughness) {
		this->textureRoughness = textureRoughness;
	}

	std::shared_ptr<Texture> getTextureShininess() {
		return this->textureShininess;
	}

	void setTextureShininess(const std::shared_ptr<Texture>& textureShininess) {
		this->textureShininess = textureShininess;
	}

	std::shared_ptr<Texture> getTextureMetalness() {
		return this->textureMetalness;
	}

	void setTextureMetalness(const std::shared_ptr<Texture>& textureMetalness) {
		this->textureMetalness = textureMetalness;
	}

	std::shared_ptr<Texture> getTextureAmbientOcclusion() {
		return this->textureAmbientOcclusion;
	}

	void setTextureAmbientOcclusion(const std::shared_ptr<Texture>& textureAmbientOcclusion) {
		this->textureAmbientOcclusion = textureAmbientOcclusion;
	}

	std::shared_ptr<Shader> getShaderPhong() {
		return this->shaderPhong;
	}

	void setShaderPhong(const std::shared_ptr<Shader>& shaderPhong) {
		this->shaderPhong = shaderPhong;
	}

	std::shared_ptr<Shader> getShaderPbr() {
		return this->shaderPBR;
	}

	void setShaderPbr(const std::shared_ptr<Shader>& shaderPbr) {
		shaderPBR = shaderPbr;
	}

	bool getUseTextureAlbedo() {
		return this->useTextureAlbedo;
	}

	void setUseTextureAlbedo(bool useTextureAlbedo) {
		this->useTextureAlbedo = useTextureAlbedo;
	}

	bool getUseTextureDiffuse() {
		return this->useTextureDiffuse;
	}

	void setUseTextureDiffuse(bool useTextureDiffuse) {
		this->useTextureDiffuse = useTextureDiffuse;
	}

	bool getUseTextureSpecular() {
		return this->useTextureSpecular;
	}

	void setUseTextureSpecular(bool useTextureSpecular) {
		this->useTextureSpecular = useTextureSpecular;
	}

	bool getUseTextureNormal() {
		return this->useTextureNormal;
	}

	void setUseTextureNormal(bool useTextureNormal) {
		this->useTextureNormal = useTextureNormal;
	}

	bool getUseTextureHeight() {
		return this->useTextureHeight;
	}

	void setUseTextureHeight(bool useTextureHeight) {
		this->useTextureHeight = useTextureHeight;
	}

	bool getUseTextureRoughness() {
		return this->useTextureRoughness;
	}

	void setUseTextureRoughness(bool useTextureRoughness) {
		this->useTextureRoughness = useTextureRoughness;
	}

	bool getUseTextureShininess() {
		return this->useTextureShininess;
	}

	void setUseTextureShininess(bool useTextureShininess) {
		this->useTextureShininess = useTextureShininess;
	}

	bool getUseTextureMetalness() {
		return this->useTextureMetalness;
	}

	void setUseTextureMetalness(bool useTextureMetalness) {
		this->useTextureMetalness = useTextureMetalness;
	}

	bool getUseTextureAmbientOcclusion() {
		return this->useTextureAmbientOcclusion;
	}

	void setUseTextureAmbientOcclusion(bool useTextureAmbientOcclusion) {
		this->useTextureAmbientOcclusion = useTextureAmbientOcclusion;
	}

	SHADING_TYPE getShadingType() {
		return this->shadingType;
	}

	void setShadingType(SHADING_TYPE shadingType) {
		this->shadingType = shadingType;
	}


};
