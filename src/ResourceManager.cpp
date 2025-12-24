#include "ResourceManager.hpp"

ResourceManager* ResourceManager::instance;

ResourceManager::ResourceManager() {
    this->drawDataList = std::vector<std::shared_ptr<DrawData>>();
    this->modelDrawDataList = std::vector<std::shared_ptr<ModelDrawData>>();
    this->meshList = std::vector<std::shared_ptr<Mesh>>();
    this->shaderList = std::vector<std::shared_ptr<Shader>>();
    this->materialList = std::vector<std::shared_ptr<Material>>();
    this->lightList = std::vector<std::shared_ptr<Light>>();
    this->textureList = std::vector<std::shared_ptr<Texture>>();
    this->cubeMapList = std::vector<std::shared_ptr<CubeMap>>();
    this->skyboxList = std::vector<std::shared_ptr<Skybox>>();
}
ResourceManager::~ResourceManager() {
    this->drawDataList.clear();
    this->modelDrawDataList.clear();
    this->meshList.clear();
    this->shaderList.clear();
    this->materialList.clear();
    this->lightList.clear();
    this->textureList.clear();
    this->cubeMapList.clear();
    this->skyboxList.clear();
    
}
ResourceManager* ResourceManager::getInstance() {
    if (!instance) {
        instance = new ResourceManager();
    }
    return instance;
}

std::filesystem::path ResourceManager::getAssetPath(const std::string& relativePath) {
    std::filesystem::path path = std::filesystem::current_path() / "res" / relativePath;
    std::filesystem::path absolutePath = std::filesystem::absolute(path);
    std::cout << "Trying to load: " << absolutePath << std::endl;
    return absolutePath;
}

std::shared_ptr<DrawData> ResourceManager::addDrawData(std::shared_ptr<DrawData> drawData) {
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

    auto found = this->getDrawDataByGUID(drawData->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->drawDataList.push_back(drawData);
    return this->drawDataList.back();
}

std::shared_ptr<ModelDrawData> ResourceManager::addModelDrawData(std::shared_ptr<ModelDrawData> modelDrawData) {
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
    auto found = this->getModelDrawDataByGUID(modelDrawData->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->modelDrawDataList.push_back(modelDrawData);
    return this->modelDrawDataList.back();
}

std::shared_ptr<LightDrawData> ResourceManager::addLightDrawData(std::shared_ptr<LightDrawData> lightDrawData) {
    this->addMesh(lightDrawData->getMesh());
    this->addShader(lightDrawData->getShader());
    auto found = this->getLightDrawDataByGUID(lightDrawData->getGUID());
    if (found != nullptr) {
        return found;
    }

    this->lightDrawDataList.push_back(lightDrawData);
    return this->lightDrawDataList.back();
}

std::shared_ptr<Mesh> ResourceManager::addMesh(std::shared_ptr<Mesh> mesh) {
    if (mesh != nullptr) {
        auto found = this->getMeshByGUID(mesh->getGUID());
        if (found != nullptr) {
            return found;
        }
        this->meshList.push_back(mesh);
    }
    return this->meshList.back();
}

std::shared_ptr<Shader> ResourceManager::addShader(std::shared_ptr<Shader> shader) {
    if (shader != nullptr) {
        auto found = this->getShaderByGUID(shader->getGUID());
        if (found != nullptr) {
            return found;
        }
        this->shaderList.push_back(shader);
    }

    return this->shaderList.back();
}

std::shared_ptr<Material> ResourceManager::addMaterial(std::shared_ptr<Material> material) {
    if (material != nullptr) {
        auto found = this->getMaterialByGUID(material->getGUID());
        if (found != nullptr) {
            return found;
        }
        this->materialList.push_back(material);
    }

    return this->materialList.back();
}

std::shared_ptr<Light> ResourceManager::addLight(std::shared_ptr<Light> light) {
    if (light != nullptr) {
        auto found = this->getLightByGUID(light->getGUID());
        if (found != nullptr) {
            return found;
        }
        this->lightList.push_back(light);
    }
    return this->lightList.back();
}

std::shared_ptr<Texture> ResourceManager::addTexture(std::shared_ptr<Texture> texture) {
    if (texture != nullptr) {
        auto found = this->getTextureByGUID(texture->getGUID());
        if (found != nullptr) {
            return found;
        }
        this->textureList.push_back(texture);
    }
    return this->textureList.back();
}

std::shared_ptr<CubeMap> ResourceManager::addCubeMap(std::shared_ptr<CubeMap> cubeMap) {
    if (cubeMap != nullptr) {
        auto found = this->getCubeMapByGUID(cubeMap->getGUID());
        if (found != nullptr) {
            return found;
        }
        this->cubeMapList.push_back(cubeMap);
    }

    return this->cubeMapList.back();
}

std::shared_ptr<Skybox> ResourceManager::addSkybox(std::shared_ptr<Skybox> skybox) {
    if (skybox != nullptr) {
        auto found = this->getSkyboxByGUID(skybox->getGUID());
        if (found != nullptr) {
            return found;
        }
        this->skyboxList.push_back(skybox);
    }
    return this->skyboxList.back();
}


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

    this->addMesh(mesh);
    this->addMaterial(material);
    this->addTexture(textureAlbedo);
    this->addTexture(textureDiffuse);
    this->addTexture(textureSpecular);
    this->addTexture(textureNormal);
    this->addTexture(textureHeight);
    this->addTexture(textureRoughness);
    this->addTexture(textureShininess);
    this->addTexture(textureMetalness);
    this->addTexture(textureAmbientOcclusion);
    this->addShader(shaderPhong);
    this->addShader(shaderPBR);

    std::shared_ptr<DrawData> drawData = std::make_shared<DrawData>(name,
        mesh,
        material,
        textureAlbedo,
        textureDiffuse,
        textureSpecular,
        textureNormal,
        textureHeight,
        textureRoughness,
        textureShininess,
        textureMetalness,
        textureAmbientOcclusion,
        shaderPhong,
        shaderPBR,
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
    auto found = this->getDrawDataByGUID(drawData->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->drawDataList.push_back(drawData);

    return this->drawDataList.back();
}

std::shared_ptr<ModelDrawData> ResourceManager::addModelDrawData(const std::string& name, const std::string& path, std::shared_ptr<Material> material, std::shared_ptr<Shader> shaderPhong, std::shared_ptr<Shader> shaderPBR, SHADING_TYPE shadingType) {
    this->addMaterial(material);
    this->addShader(shaderPhong);
    this->addShader(shaderPBR);
    std::shared_ptr<ModelDrawData> modelDrawData = std::make_shared<ModelDrawData>(name, path, material, shaderPhong, shaderPBR, true, true, true, true, true, true, true, true, true, shadingType);
    this->addTexture(modelDrawData->getTextureAlbedo());
    this->addTexture(modelDrawData->getTextureDiffuse());
    this->addTexture(modelDrawData->getTextureSpecular());
    this->addTexture(modelDrawData->getTextureNormal());
    this->addTexture(modelDrawData->getTextureHeight());
    this->addTexture(modelDrawData->getTextureRoughness());
    this->addTexture(modelDrawData->getTextureShininess());
    this->addTexture(modelDrawData->getTextureMetalness());
    this->addTexture(modelDrawData->getTextureAmbientOcclusion());
    this->addMesh(modelDrawData->getMesh());
    auto found = this->getModelDrawDataByGUID(modelDrawData->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->modelDrawDataList.push_back(modelDrawData);
    return this->modelDrawDataList.back();
}

std::shared_ptr<LightDrawData> ResourceManager::addLightDrawData(const std::string& name, std::shared_ptr<Light> light, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader) {
    this->addMesh(mesh);
    this->addShader(shader);
    std::shared_ptr<LightDrawData> lightDrawData = std::make_shared<LightDrawData>(name, light, mesh, shader);
    auto found = this->getLightDrawDataByGUID(lightDrawData->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->lightDrawDataList.push_back(lightDrawData);
    return this->lightDrawDataList.back();
}

std::shared_ptr<Mesh> ResourceManager::addMesh(const std::string& name, std::shared_ptr<Geometry> singleGeometry) {
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(name, singleGeometry);
    auto found = this->getMeshByGUID(mesh->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->meshList.push_back(mesh);
    return this->meshList.back();
}

std::shared_ptr<Mesh> ResourceManager::addMesh(const std::string& name,
std::vector<std::shared_ptr<Geometry>> geometryList) {
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(name, geometryList);
    auto found = this->getMeshByGUID(mesh->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->meshList.push_back(mesh);
    return this->meshList.back();
}

std::shared_ptr<Shader> ResourceManager::addShader(const std::string& name, const std::string& vertexShaderPath,
const std::string& fragmentShaderPath, SHADING_TYPE shaderType) {
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(name, vertexShaderPath, fragmentShaderPath, shaderType);
    auto found = this->getShaderByGUID(shader->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->shaderList.push_back(shader);
    return this->shaderList.back();
}

std::shared_ptr<Material> ResourceManager::addMaterial(const std::string& name, glm::vec4 albedo, glm::vec3 ambient, glm::vec3 diffuse,
glm::vec3 specular, float shininess) {
    std::shared_ptr<Material> material = std::make_shared<Material>(name, albedo, ambient, diffuse, specular, shininess);
    auto found = this->getMaterialByGUID(material->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->materialList.push_back(material);
    return this->materialList.back();
}

std::shared_ptr<Light> ResourceManager::addLight(const std::string& name, glm::vec4 albedo, glm::vec3 ambient,
    glm::vec3 diffuse, glm::vec3 specular) {
    std::shared_ptr<Light> light = std::make_shared<Light>(name, albedo, ambient, diffuse, specular);
    auto found = this->getLightByGUID(light->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->lightList.push_back(light);
    return this->lightList.back();
}


std::shared_ptr<Texture> ResourceManager::addTexture(const std::string& name, const std::string& path, TextureType textureType) {
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(name, path, textureType);
    auto found = this->getTextureByGUID(texture->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->textureList.push_back(texture);
    return this->textureList.back();
}

std::shared_ptr<CubeMap> ResourceManager::addCubeMap(const std::string& name, std::vector<std::string> facePaths) {
    std::shared_ptr<CubeMap> cubeMap = std::make_shared<CubeMap>(name, facePaths);
    auto found = this->getCubeMapByGUID(cubeMap->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->cubeMapList.push_back(cubeMap);
    return this->cubeMapList.back();
}


std::shared_ptr<Skybox> ResourceManager::addSkybox(const std::string& name, float colorX, float colorY, float colorZ, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<CubeMap> cubeMap) {
    this->addMesh(mesh);
    this->addShader(shader);
    this->addCubeMap(cubeMap);
    std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>(name, colorX, colorY, colorZ, mesh, shader, cubeMap);
    auto found = this->getSkyboxByGUID(skybox->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->skyboxList.push_back(skybox);
    return this->skyboxList.back();
}


std::shared_ptr<DrawData> ResourceManager::getDrawDataByGUID(const std::string& guid) {
    for (auto current : this->drawDataList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<ModelDrawData> ResourceManager::getModelDrawDataByGUID(const std::string& guid) {
    for (auto current : this->modelDrawDataList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<LightDrawData> ResourceManager::getLightDrawDataByGUID(const std::string& guid) {
    for (auto current : this->lightDrawDataList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Mesh> ResourceManager::getMeshByGUID(const std::string& guid) {
    for (auto current : this->meshList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Shader> ResourceManager::getShaderByGUID(const std::string& guid) {
    for (auto current : this->shaderList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Material> ResourceManager::getMaterialByGUID(const std::string& guid) {
    for (auto current : this->materialList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}
std::shared_ptr<Light> ResourceManager::getLightByGUID(const std::string& guid) {
    for (auto current : this->lightList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Texture> ResourceManager::getTextureByGUID(const std::string& guid) {
    for (auto current : this->textureList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<CubeMap> ResourceManager::getCubeMapByGUID(const std::string& guid) {
    for (auto current : this->cubeMapList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Skybox> ResourceManager::getSkyboxByGUID(const std::string& guid) {
    for (auto current : this->skyboxList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<DrawData> ResourceManager::getDrawDataByName(const std::string& name) {
    for (auto current : this->drawDataList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<ModelDrawData> ResourceManager::getModelDrawDataByName(const std::string& name) {
    for (auto current : this->modelDrawDataList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<LightDrawData> ResourceManager::getLightDrawDataByName(const std::string& name) {
    for (auto current : this->lightDrawDataList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Mesh> ResourceManager::getMeshByName(const std::string& name) {
    for (auto current : this->meshList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Shader> ResourceManager::getShaderByName(const std::string& name) {
    for (auto current : this->shaderList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Material> ResourceManager::getMaterialByName(const std::string& name) {
    for (auto current : this->materialList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Texture> ResourceManager::getTextureByName(const std::string& name) {
    for (auto current : this->textureList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<CubeMap> ResourceManager::getCubeMapByName(const std::string& name) {
    for (auto current : this->cubeMapList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<Skybox> ResourceManager::getSkyboxByName(const std::string& name) {
    for (auto current : this->skyboxList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

void ResourceManager::clear(bool reinitialize) {

}
