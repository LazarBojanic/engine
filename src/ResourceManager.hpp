#pragma once

#include "Util.hpp"
#include "DrawData.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "ModelDrawData.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "CubeMap.hpp"
#include "LightDrawData.hpp"
#include "Skybox.hpp"

class ResourceManager{
private:
	ResourceManager();
	~ResourceManager();
	static ResourceManager* instance;

	std::vector<std::shared_ptr<DrawData>> drawDataList;
	std::vector<std::shared_ptr<ModelDrawData>> modelDrawDataList;
	std::vector<std::shared_ptr<LightDrawData>> lightDrawDataList;

	std::vector<std::shared_ptr<Mesh>> meshList;
	std::vector<std::shared_ptr<Shader>> shaderList;
	std::vector<std::shared_ptr<Light>> lightList;
	std::vector<std::shared_ptr<Material>> materialList;
	std::vector<std::shared_ptr<Texture>> textureList;
	std::vector<std::shared_ptr<CubeMap>> cubeMapList;
	std::vector<std::shared_ptr<Skybox>> skyboxList;
public:
	static ResourceManager* getInstance();

	std::shared_ptr<DrawData> addDrawData(std::shared_ptr<DrawData> drawData);
	std::shared_ptr<ModelDrawData> addModelDrawData(std::shared_ptr<ModelDrawData> modelDrawData);
	std::shared_ptr<LightDrawData> addLightDrawData(std::shared_ptr<LightDrawData> lightDrawData);
	std::shared_ptr<Mesh> addMesh(std::shared_ptr<Mesh> mesh);
	std::shared_ptr<Shader> addShader(std::shared_ptr<Shader> shader);
	std::shared_ptr<Material> addMaterial(std::shared_ptr<Material> material);
	std::shared_ptr<Light> addLight(std::shared_ptr<Light> light);
	std::shared_ptr<Texture> addTexture(std::shared_ptr<Texture> texture);
	std::shared_ptr<CubeMap> addCubeMap(std::shared_ptr<CubeMap> cubeMap);
	std::shared_ptr<Skybox> addSkybox(std::shared_ptr<Skybox> skybox);

	std::shared_ptr<DrawData> addDrawData(const std::string& name, std::shared_ptr<Mesh> mesh,
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
	std::shared_ptr<ModelDrawData> addModelDrawData(const std::string& name, const std::string& path, std::shared_ptr<Material> material, std::shared_ptr<Shader> shaderPhong, std::shared_ptr<Shader> shaderPBR, SHADING_TYPE shadingType);
	std::shared_ptr<LightDrawData> addLightDrawData(const std::string& name, std::shared_ptr<Light> light, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader);
	std::shared_ptr<Mesh> addMesh(const std::string& name, std::shared_ptr<Geometry> singleGeometry);
	std::shared_ptr<Mesh> addMesh(const std::string& name, std::vector<std::shared_ptr<Geometry>> geometryList);
	std::shared_ptr<Shader> addShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, SHADING_TYPE shaderType);
	std::shared_ptr<Material> addMaterial(const std::string& name, glm::vec4 albedo, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	std::shared_ptr<Light> addLight(const std::string& name, glm::vec4 albedo, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	std::shared_ptr<Texture> addTexture(const std::string& name, const std::string& path, TextureType textureType);
	std::shared_ptr<CubeMap> addCubeMap(const std::string& name, std::vector<std::string> facePaths);
	std::shared_ptr<Skybox> addSkybox(const std::string& name, float colorX, float colorY, float colorZ, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<CubeMap> cubeMap);

	std::shared_ptr<DrawData> getDrawDataByGUID(const std::string& guid);
	std::shared_ptr<ModelDrawData> getModelDrawDataByGUID(const std::string& guid);
	std::shared_ptr<LightDrawData> getLightDrawDataByGUID(const std::string& guid);
	std::shared_ptr<Mesh> getMeshByGUID(const std::string& guid);
	std::shared_ptr<Shader> getShaderByGUID(const std::string& guid);
	std::shared_ptr<Material> getMaterialByGUID(const std::string& guid);
	std::shared_ptr<Light> getLightByGUID(const std::string& guid);
	std::shared_ptr<Texture> getTextureByGUID(const std::string& guid);
	std::shared_ptr<CubeMap> getCubeMapByGUID(const std::string& guid);
	std::shared_ptr<Skybox> getSkyboxByGUID(const std::string& guid);

	std::shared_ptr<DrawData> getDrawDataByName(const std::string& name);
	std::shared_ptr<ModelDrawData> getModelDrawDataByName(const std::string& name);
	std::shared_ptr<LightDrawData> getLightDrawDataByName(const std::string& name);
	std::shared_ptr<Mesh> getMeshByName(const std::string& name);
	std::shared_ptr<Shader> getShaderByName(const std::string& name);
	std::shared_ptr<Material> getMaterialByName(const std::string& name);
	std::shared_ptr<Texture> getTextureByName(const std::string& name);
	std::shared_ptr<CubeMap> getCubeMapByName(const std::string& name);
	std::shared_ptr<Skybox> getSkyboxByName(const std::string& name);
	

	void clear(bool reinitialize);
};