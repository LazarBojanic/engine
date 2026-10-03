#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Geometry.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Util.hpp"

class ModelDrawData {
private:
	std::string guid;
	std::string name;
	std::string directory;
	std::string path;
	bool gammaCorrection;
	std::shared_ptr<Mesh> mesh;
	std::vector<std::shared_ptr<Geometry>> tempGeometryList;
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
	ModelDrawData();
	ModelDrawData(const std::string& name, const std::string& path, std::shared_ptr<Material> material, std::shared_ptr<Shader> shaderPhong, std::shared_ptr<Shader> shaderPBR,
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


	~ModelDrawData();
	void loadAssimpModel(const std::string& path);
	void processAssimpModelNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Geometry> processAssimpMesh(aiMesh* mesh, const aiScene* scene);
	void loadMaterialTextures(aiMaterial* aiMaterial, aiTextureType type);

	const std::string& getGUID() const {
		return this->guid;
	}

	const std::string& getName() const {
		return this->name;
	}

	const std::string& getDirectory() const {
		return this->directory;
	}

	const std::string& getPath() const {
		return this->path;
	}

	bool getGammaCorrection() const {
		return this->gammaCorrection;
	}

	const std::shared_ptr<Mesh>& getMesh() const {
		return this->mesh;
	}

	const std::shared_ptr<Material>& getMaterial() const {
		return this->material;
	}

	const std::shared_ptr<Texture>& getTextureAlbedo() const {
		return this->textureAlbedo;
	}

	void setTextureAlbedo(const std::shared_ptr<Texture>& textureAlbedo) {
		this->textureAlbedo = textureAlbedo;
	}

	const std::shared_ptr<Texture>& getTextureDiffuse() const {
		return this->textureDiffuse;
	}

	void setTextureDiffuse(const std::shared_ptr<Texture>& textureDiffuse) {
		this->textureDiffuse = textureDiffuse;
	}

	const std::shared_ptr<Texture>& getTextureSpecular() const {
		return this->textureSpecular;
	}

	void setTextureSpecular(const std::shared_ptr<Texture>& textureSpecular) {
		this->textureSpecular = textureSpecular;
	}

	const std::shared_ptr<Texture>& getTextureNormal() const {
		return this->textureNormal;
	}

	void setTextureNormal(const std::shared_ptr<Texture>& textureNormal) {
		this->textureNormal = textureNormal;
	}

	const std::shared_ptr<Texture>& getTextureHeight() const {
		return this->textureHeight;
	}

	void setTextureHeight(const std::shared_ptr<Texture>& textureHeight) {
		this->textureHeight = textureHeight;
	}

	const std::shared_ptr<Texture>& getTextureRoughness() const {
		return this->textureRoughness;
	}

	void setTextureRoughness(const std::shared_ptr<Texture>& textureRoughness) {
		this->textureRoughness = textureRoughness;
	}

	const std::shared_ptr<Texture>& getTextureShininess() const {
		return this->textureShininess;
	}

	void setTextureShininess(const std::shared_ptr<Texture>& textureShininess) {
		this->textureShininess = textureShininess;
	}

	const std::shared_ptr<Texture>& getTextureMetalness() const {
		return this->textureMetalness;
	}

	void setTextureMetalness(const std::shared_ptr<Texture>& textureMetalness) {
		this->textureMetalness = textureMetalness;
	}

	const std::shared_ptr<Texture>& getTextureAmbientOcclusion() const {
		return this->textureAmbientOcclusion;
	}

	void setTextureAmbientOcclusion(const std::shared_ptr<Texture>& textureAmbientOcclusion) {
		this->textureAmbientOcclusion = textureAmbientOcclusion;
	}

	const std::shared_ptr<Shader>& getShaderPhong() const {
		return this->shaderPhong;
	}

	void setShaderPhong(const std::shared_ptr<Shader>& shaderPhong) {
		this->shaderPhong = shaderPhong;
	}

	const std::shared_ptr<Shader>& getShaderPbr() const {
		return this->shaderPBR;
	}

	void setShaderPbr(const std::shared_ptr<Shader>& shaderPbr) {
		this->shaderPBR = shaderPbr;
	}

	bool getUseTextureAlbedo() const {
		return this->useTextureAlbedo;
	}

	void setUseTextureAlbedo(bool useTextureAlbedo) {
		this->useTextureAlbedo = useTextureAlbedo;
	}

	bool getUseTextureDiffuse() const {
		return this->useTextureDiffuse;
	}

	void setUseTextureDiffuse(bool useTextureDiffuse) {
		this->useTextureDiffuse = useTextureDiffuse;
	}

	bool getUseTextureSpecular() const {
		return this->useTextureSpecular;
	}

	void setUseTextureSpecular(bool useTextureSpecular) {
		this->useTextureSpecular = useTextureSpecular;
	}

	bool getUseTextureNormal() const {
		return this->useTextureNormal;
	}

	void setUseTextureNormal(bool useTextureNormal) {
		this->useTextureNormal = useTextureNormal;
	}

	bool getUseTextureHeight() const {
		return this->useTextureHeight;
	}

	void setUseTextureHeight(bool useTextureHeight) {
		this->useTextureHeight = useTextureHeight;
	}

	bool getUseTextureRoughness() const {
		return this->useTextureRoughness;
	}

	void setUseTextureRoughness(bool useTextureRoughness) {
		this->useTextureRoughness = useTextureRoughness;
	}

	bool getUseTextureShininess() const {
		return this->useTextureShininess;
	}

	void setUseTextureShininess(bool useTextureShininess) {
		this->useTextureShininess = useTextureShininess;
	}

	bool getUseTextureMetalness() const {
		return this->useTextureMetalness;
	}

	void setUseTextureMetalness(bool useTextureMetalness) {
		this->useTextureMetalness = useTextureMetalness;
	}

	bool getUseTextureAmbientOcclusion() const {
		return this->useTextureAmbientOcclusion;
	}

	void setUseTextureAmbientOcclusion(bool useTextureAmbientOcclusion) {
		this->useTextureAmbientOcclusion = useTextureAmbientOcclusion;
	}

	SHADING_TYPE getShadingType() const {
		return this->shadingType;
	}

	void setShadingType(SHADING_TYPE shadingType) {
		this->shadingType = shadingType;
	}
};
