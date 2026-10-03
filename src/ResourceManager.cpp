#include "ResourceManager.hpp"

ResourceManager* ResourceManager::instance;

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
    this->clear(false);
}

ResourceManager* ResourceManager::getInstance() {
    if (!instance) {
        instance = new ResourceManager();
    }
    return instance;
}

std::filesystem::path ResourceManager::getAssetPath(const std::string& relativePath) {
    const std::filesystem::path path = std::filesystem::current_path() / "res" / relativePath;
    const std::filesystem::path absolutePath = std::filesystem::absolute(path);
    std::cout << "Trying to load: " << absolutePath.generic_string() << std::endl;
    return absolutePath;
}

std::shared_ptr<DrawData> ResourceManager::addDrawData(std::shared_ptr<DrawData> drawData) {
    if (drawData == nullptr) {
        return nullptr;
    }
    this->addMesh(drawData->getMesh());
    this->addMaterial(drawData->getMaterial());
    this->addTexture(drawData->getTextureAlbedo());
    this->addTexture(drawData->getTextureDiffuse());
    this->addTexture(drawData->getTextureSpecular());
    this->addTexture(drawData->getTextureNormal());
    this->addTexture(drawData->getTextureHeight());
    this->addTexture(drawData->getTextureRoughness());
    this->addTexture(drawData->getTextureShininess());
    this->addTexture(drawData->getTextureMetalness());
    this->addTexture(drawData->getTextureAmbientOcclusion());
    this->addShader(drawData->getShaderPhong());
    this->addShader(drawData->getShaderPbr());
    return this->addResource(std::move(drawData), this->drawDataList, this->drawDataByGuid);
}

std::shared_ptr<ModelDrawData> ResourceManager::addModelDrawData(std::shared_ptr<ModelDrawData> modelDrawData) {
    if (modelDrawData == nullptr) {
        return nullptr;
    }
    this->addMesh(modelDrawData->getMesh());
    this->addMaterial(modelDrawData->getMaterial());
    this->addTexture(modelDrawData->getTextureAlbedo());
    this->addTexture(modelDrawData->getTextureDiffuse());
    this->addTexture(modelDrawData->getTextureSpecular());
    this->addTexture(modelDrawData->getTextureNormal());
    this->addTexture(modelDrawData->getTextureHeight());
    this->addTexture(modelDrawData->getTextureRoughness());
    this->addTexture(modelDrawData->getTextureShininess());
    this->addTexture(modelDrawData->getTextureMetalness());
    this->addTexture(modelDrawData->getTextureAmbientOcclusion());
    this->addShader(modelDrawData->getShaderPhong());
    this->addShader(modelDrawData->getShaderPbr());
    return this->addResource(std::move(modelDrawData), this->modelDrawDataList, this->modelDrawDataByGuid);
}

std::shared_ptr<LightDrawData> ResourceManager::addLightDrawData(std::shared_ptr<LightDrawData> lightDrawData) {
    if (lightDrawData == nullptr) {
        return nullptr;
    }
    this->addMesh(lightDrawData->getMesh());
    this->addShader(lightDrawData->getShader());
    return this->addResource(std::move(lightDrawData), this->lightDrawDataList, this->lightDrawDataByGuid);
}

std::shared_ptr<Mesh> ResourceManager::addMesh(std::shared_ptr<Mesh> mesh) {
    return this->addResource(std::move(mesh), this->meshList, this->meshByGuid);
}

std::shared_ptr<Shader> ResourceManager::addShader(std::shared_ptr<Shader> shader) {
    return this->addResource(std::move(shader), this->shaderList, this->shaderByGuid);
}

std::shared_ptr<Material> ResourceManager::addMaterial(std::shared_ptr<Material> material) {
    return this->addResource(std::move(material), this->materialList, this->materialByGuid);
}

std::shared_ptr<Light> ResourceManager::addLight(std::shared_ptr<Light> light) {
    return this->addResource(std::move(light), this->lightList, this->lightByGuid);
}

std::shared_ptr<Texture> ResourceManager::addTexture(std::shared_ptr<Texture> texture) {
    return this->addResource(std::move(texture), this->textureList, this->textureByGuid);
}

std::shared_ptr<CubeMap> ResourceManager::addCubeMap(std::shared_ptr<CubeMap> cubeMap) {
    return this->addResource(std::move(cubeMap), this->cubeMapList, this->cubeMapByGuid);
}

std::shared_ptr<Skybox> ResourceManager::addSkybox(std::shared_ptr<Skybox> skybox) {
    if (skybox == nullptr) {
        return nullptr;
    }
    this->addMesh(skybox->getMesh());
    this->addShader(skybox->getShader());
    this->addCubeMap(skybox->getCubeMap());
    return this->addResource(std::move(skybox), this->skyboxList, this->skyboxByGuid);
}

std::shared_ptr<DrawData> ResourceManager::addDrawData(const std::string& name, std::shared_ptr<Mesh> mesh,
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
    std::shared_ptr<DrawData> drawData = std::make_shared<DrawData>(name,
        std::move(mesh),
        std::move(material),
        std::move(textureAlbedo),
        std::move(textureDiffuse),
        std::move(textureSpecular),
        std::move(textureNormal),
        std::move(textureHeight),
        std::move(textureRoughness),
        std::move(textureShininess),
        std::move(textureMetalness),
        std::move(textureAmbientOcclusion),
        std::move(shaderPhong),
        std::move(shaderPBR),
        useTextureAlbedo,
        useTextureDiffuse,
        useTextureSpecular,
        useTextureNormal,
        useTextureHeight,
        useTextureRoughness,
        useTextureShininess,
        useTextureMetalness,
        useTextureAmbientOcclusion,
        shadingType);
    return this->addDrawData(std::move(drawData));
}

std::shared_ptr<ModelDrawData> ResourceManager::addModelDrawData(const std::string& name, const std::string& path, std::shared_ptr<Material> material, std::shared_ptr<Shader> shaderPhong, std::shared_ptr<Shader> shaderPBR, SHADING_TYPE shadingType) {
    std::shared_ptr<ModelDrawData> modelDrawData = std::make_shared<ModelDrawData>(name, path,
        std::move(material), std::move(shaderPhong), std::move(shaderPBR),
        true, true, true, true, true, true, true, true, true, shadingType);
    return this->addModelDrawData(std::move(modelDrawData));
}

std::shared_ptr<LightDrawData> ResourceManager::addLightDrawData(const std::string& name, std::shared_ptr<Light> light, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader) {
    this->addMesh(mesh);
    this->addShader(shader);
    std::shared_ptr<LightDrawData> lightDrawData = std::make_shared<LightDrawData>(name, std::move(light), std::move(mesh), std::move(shader));
    return this->addLightDrawData(std::move(lightDrawData));
}

std::shared_ptr<Mesh> ResourceManager::addMesh(const std::string& name, std::shared_ptr<Geometry> singleGeometry) {
    return this->addMesh(std::make_shared<Mesh>(name, std::move(singleGeometry)));
}

std::shared_ptr<Mesh> ResourceManager::addMesh(const std::string& name, std::vector<std::shared_ptr<Geometry>> geometryList) {
    return this->addMesh(std::make_shared<Mesh>(name, std::move(geometryList)));
}

std::shared_ptr<Shader> ResourceManager::addShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, SHADING_TYPE shaderType) {
    return this->addShader(std::make_shared<Shader>(name, vertexShaderPath, fragmentShaderPath, shaderType));
}

std::shared_ptr<Material> ResourceManager::addMaterial(const std::string& name, glm::vec4 albedo, glm::vec3 ambient, glm::vec3 diffuse,
    glm::vec3 specular, float shininess) {
    return this->addMaterial(std::make_shared<Material>(name, albedo, ambient, diffuse, specular, shininess));
}

std::shared_ptr<Light> ResourceManager::addLight(const std::string& name, glm::vec4 albedo, glm::vec3 ambient,
    glm::vec3 diffuse, glm::vec3 specular) {
    return this->addLight(std::make_shared<Light>(name, albedo, ambient, diffuse, specular));
}

std::shared_ptr<Texture> ResourceManager::addTexture(const std::string& name, const std::string& path, TextureType textureType) {
    return this->addTexture(std::make_shared<Texture>(name, path, textureType));
}

std::shared_ptr<CubeMap> ResourceManager::addCubeMap(const std::string& name, std::vector<std::string> facePaths) {
    return this->addCubeMap(std::make_shared<CubeMap>(name, std::move(facePaths)));
}

std::shared_ptr<Skybox> ResourceManager::addSkybox(const std::string& name, float colorX, float colorY, float colorZ, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<CubeMap> cubeMap) {
    std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>(name, colorX, colorY, colorZ, std::move(mesh), std::move(shader), std::move(cubeMap));
    return this->addSkybox(std::move(skybox));
}

std::shared_ptr<DrawData> ResourceManager::getDrawDataByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->drawDataByGuid);
}

std::shared_ptr<ModelDrawData> ResourceManager::getModelDrawDataByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->modelDrawDataByGuid);
}

std::shared_ptr<LightDrawData> ResourceManager::getLightDrawDataByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->lightDrawDataByGuid);
}

std::shared_ptr<Mesh> ResourceManager::getMeshByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->meshByGuid);
}

std::shared_ptr<Shader> ResourceManager::getShaderByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->shaderByGuid);
}

std::shared_ptr<Material> ResourceManager::getMaterialByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->materialByGuid);
}

std::shared_ptr<Light> ResourceManager::getLightByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->lightByGuid);
}

std::shared_ptr<Texture> ResourceManager::getTextureByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->textureByGuid);
}

std::shared_ptr<CubeMap> ResourceManager::getCubeMapByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->cubeMapByGuid);
}

std::shared_ptr<Skybox> ResourceManager::getSkyboxByGUID(const std::string& guid) {
    return this->getByGUID(guid, this->skyboxByGuid);
}

std::shared_ptr<DrawData> ResourceManager::getDrawDataByName(const std::string& name) {
    return this->getByName(name, this->drawDataList);
}

std::shared_ptr<ModelDrawData> ResourceManager::getModelDrawDataByName(const std::string& name) {
    return this->getByName(name, this->modelDrawDataList);
}

std::shared_ptr<LightDrawData> ResourceManager::getLightDrawDataByName(const std::string& name) {
    return this->getByName(name, this->lightDrawDataList);
}

std::shared_ptr<Mesh> ResourceManager::getMeshByName(const std::string& name) {
    return this->getByName(name, this->meshList);
}

std::shared_ptr<Shader> ResourceManager::getShaderByName(const std::string& name) {
    return this->getByName(name, this->shaderList);
}

std::shared_ptr<Material> ResourceManager::getMaterialByName(const std::string& name) {
    return this->getByName(name, this->materialList);
}

std::shared_ptr<Texture> ResourceManager::getTextureByName(const std::string& name) {
    return this->getByName(name, this->textureList);
}

std::shared_ptr<CubeMap> ResourceManager::getCubeMapByName(const std::string& name) {
    return this->getByName(name, this->cubeMapList);
}

std::shared_ptr<Skybox> ResourceManager::getSkyboxByName(const std::string& name) {
    return this->getByName(name, this->skyboxList);
}

void ResourceManager::clear(bool reinitialize) {
    this->drawDataList.clear();
    this->modelDrawDataList.clear();
    this->lightDrawDataList.clear();
    this->meshList.clear();
    this->shaderList.clear();
    this->lightList.clear();
    this->materialList.clear();
    this->textureList.clear();
    this->cubeMapList.clear();
    this->skyboxList.clear();
    this->drawDataByGuid.clear();
    this->modelDrawDataByGuid.clear();
    this->lightDrawDataByGuid.clear();
    this->meshByGuid.clear();
    this->shaderByGuid.clear();
    this->lightByGuid.clear();
    this->materialByGuid.clear();
    this->textureByGuid.clear();
    this->cubeMapByGuid.clear();
    this->skyboxByGuid.clear();
}
