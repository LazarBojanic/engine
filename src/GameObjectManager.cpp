#include "GameObjectManager.hpp"

#include <algorithm>

GameObjectManager* GameObjectManager::instance;

GameObjectManager::GameObjectManager() {
}

GameObjectManager::~GameObjectManager() {
}

GameObjectManager* GameObjectManager::getInstance() {
    if (!instance) {
        instance = new GameObjectManager();
    }
    return instance;
}

void GameObjectManager::clear(bool reinitialize) {
    this->gameObjectList.clear();
    this->modelGameObjectList.clear();
    this->lightGameObjectList.clear();
    this->gameObjectByGuid.clear();
    this->modelGameObjectByGuid.clear();
    this->lightGameObjectByGuid.clear();
}

std::shared_ptr<GameObject> GameObjectManager::addGameObject(std::shared_ptr<GameObject> gameObject) {
    if (gameObject == nullptr) {
        return nullptr;
    }
    const auto found = this->gameObjectByGuid.find(gameObject->getGUID());
    if (found != this->gameObjectByGuid.end()) {
        return found->second;
    }
    if (gameObject->getDrawData() != nullptr && gameObject->getDrawData()->getMesh() != nullptr) {
        const std::shared_ptr<Mesh>& mesh = gameObject->getDrawData()->getMesh();
        gameObject->getTransform().setLocalBounds(mesh->getLocalMin(), mesh->getLocalMax());
    }
    this->gameObjectByGuid.emplace(gameObject->getGUID(), gameObject);
    this->gameObjectList.push_back(std::move(gameObject));
    return this->gameObjectList.back();
}

std::shared_ptr<GameObject> GameObjectManager::addGameObject(const std::string& name, const std::string& tag,
    std::shared_ptr<DrawData> drawData,
    float positionX, float positionY, float positionZ,
    float sizeX, float sizeY, float sizeZ,
    float scaleX, float scaleY, float scaleZ,
    float rotationX, float rotationY, float rotationZ,
    float speedX, float speedY, float speedZ,
    bool isHit) {
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name, tag, std::move(drawData),
        positionX, positionY, positionZ,
        sizeX, sizeY, sizeZ,
        scaleX, scaleY, scaleZ,
        rotationX, rotationY, rotationZ,
        speedX, speedY, speedZ,
        isHit);
    return this->addGameObject(std::move(gameObject));
}

std::shared_ptr<ModelGameObject> GameObjectManager::addModelGameObject(std::shared_ptr<ModelGameObject> modelGameObject) {
    if (modelGameObject == nullptr) {
        return nullptr;
    }
    const auto found = this->modelGameObjectByGuid.find(modelGameObject->getGUID());
    if (found != this->modelGameObjectByGuid.end()) {
        return found->second;
    }
    if (modelGameObject->getModelDrawData() != nullptr && modelGameObject->getModelDrawData()->getMesh() != nullptr) {
        const std::shared_ptr<Mesh>& mesh = modelGameObject->getModelDrawData()->getMesh();
        modelGameObject->getTransform().setLocalBounds(mesh->getLocalMin(), mesh->getLocalMax());
    }
    this->modelGameObjectByGuid.emplace(modelGameObject->getGUID(), modelGameObject);
    this->modelGameObjectList.push_back(std::move(modelGameObject));
    return this->modelGameObjectList.back();
}

std::shared_ptr<ModelGameObject> GameObjectManager::addModelGameObject(const std::string& name, const std::string& tag, std::shared_ptr<ModelDrawData> modelDrawData,
    float positionX, float positionY, float positionZ,
    float sizeX, float sizeY, float sizeZ,
    float scaleX, float scaleY, float scaleZ,
    float rotationX, float rotationY, float rotationZ,
    float speedX, float speedY, float speedZ,
    bool isHit) {
    std::shared_ptr<ModelGameObject> modelGameObject = std::make_shared<ModelGameObject>(name, tag, std::move(modelDrawData),
        positionX, positionY, positionZ,
        sizeX, sizeY, sizeZ,
        scaleX, scaleY, scaleZ,
        rotationX, rotationY, rotationZ,
        speedX, speedY, speedZ,
        isHit);
    return this->addModelGameObject(std::move(modelGameObject));
}

std::shared_ptr<LightGameObject> GameObjectManager::addLightGameObject(std::shared_ptr<LightGameObject> lightGameObject) {
    if (lightGameObject == nullptr) {
        return nullptr;
    }
    const auto found = this->lightGameObjectByGuid.find(lightGameObject->getGUID());
    if (found != this->lightGameObjectByGuid.end()) {
        return found->second;
    }
    if (lightGameObject->getLightDrawData() != nullptr && lightGameObject->getLightDrawData()->getMesh() != nullptr) {
        const std::shared_ptr<Mesh>& mesh = lightGameObject->getLightDrawData()->getMesh();
        lightGameObject->getTransform().setLocalBounds(mesh->getLocalMin(), mesh->getLocalMax());
    }
    this->lightGameObjectByGuid.emplace(lightGameObject->getGUID(), lightGameObject);
    this->lightGameObjectList.push_back(std::move(lightGameObject));
    return this->lightGameObjectList.back();
}

std::shared_ptr<LightGameObject> GameObjectManager::addLightGameObject(const std::string& name, const std::string& tag, std::shared_ptr<LightDrawData> lightDrawData,
    float positionX, float positionY, float positionZ,
    float sizeX, float sizeY, float sizeZ,
    float scaleX, float scaleY, float scaleZ,
    float rotationX, float rotationY, float rotationZ,
    float speedX, float speedY, float speedZ,
    bool isHit) {
    std::shared_ptr<LightGameObject> lightGameObject = std::make_shared<LightGameObject>(name, tag, std::move(lightDrawData),
        positionX, positionY, positionZ,
        sizeX, sizeY, sizeZ,
        scaleX, scaleY, scaleZ,
        rotationX, rotationY, rotationZ,
        speedX, speedY, speedZ,
        isHit);
    return this->addLightGameObject(std::move(lightGameObject));
}

std::shared_ptr<GameObject> GameObjectManager::getGameObjectByGUID(const std::string& guid) {
    const auto found = this->gameObjectByGuid.find(guid);
    return found != this->gameObjectByGuid.end() ? found->second : nullptr;
}

std::shared_ptr<GameObject> GameObjectManager::getGameObjectByName(const std::string& name) {
    for (const auto& current : this->gameObjectList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<GameObject> GameObjectManager::getGameObjectByTag(const std::string& tag) {
    for (const auto& current : this->gameObjectList) {
        if (current->getTag() == tag) {
            return current;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<GameObject>> GameObjectManager::getGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<GameObject>> result;
    for (const auto& current : this->gameObjectList) {
        if (current->getTag() == tag) {
            result.push_back(current);
        }
    }
    return result;
}

void GameObjectManager::removeGameObjectByGUID(const std::string& guid) {
    this->gameObjectByGuid.erase(guid);
    this->gameObjectList.erase(
        std::remove_if(this->gameObjectList.begin(), this->gameObjectList.end(),
            [&guid](const std::shared_ptr<GameObject>& current) { return current->getGUID() == guid; }),
        this->gameObjectList.end());
}

void GameObjectManager::removeGameObjectsByTag(const std::string& tag) {
    for (const auto& current : this->gameObjectList) {
        if (current->getTag() == tag) {
            this->gameObjectByGuid.erase(current->getGUID());
        }
    }
    this->gameObjectList.erase(
        std::remove_if(this->gameObjectList.begin(), this->gameObjectList.end(),
            [&tag](const std::shared_ptr<GameObject>& current) { return current->getTag() == tag; }),
        this->gameObjectList.end());
}

std::shared_ptr<ModelGameObject> GameObjectManager::getModelGameObjectByGUID(const std::string& guid) {
    const auto found = this->modelGameObjectByGuid.find(guid);
    return found != this->modelGameObjectByGuid.end() ? found->second : nullptr;
}

std::shared_ptr<ModelGameObject> GameObjectManager::getModelGameObjectByName(const std::string& name) {
    for (const auto& current : this->modelGameObjectList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<ModelGameObject> GameObjectManager::getModelGameObjectByTag(const std::string& tag) {
    for (const auto& current : this->modelGameObjectList) {
        if (current->getTag() == tag) {
            return current;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<ModelGameObject>> GameObjectManager::getModelGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<ModelGameObject>> result;
    for (const auto& current : this->modelGameObjectList) {
        if (current->getTag() == tag) {
            result.push_back(current);
        }
    }
    return result;
}

void GameObjectManager::removeModelGameObjectByGUID(const std::string& guid) {
    this->modelGameObjectByGuid.erase(guid);
    this->modelGameObjectList.erase(
        std::remove_if(this->modelGameObjectList.begin(), this->modelGameObjectList.end(),
            [&guid](const std::shared_ptr<ModelGameObject>& current) { return current->getGUID() == guid; }),
        this->modelGameObjectList.end());
}

void GameObjectManager::removeModelGameObjectsByTag(const std::string& tag) {
    for (const auto& current : this->modelGameObjectList) {
        if (current->getTag() == tag) {
            this->modelGameObjectByGuid.erase(current->getGUID());
        }
    }
    this->modelGameObjectList.erase(
        std::remove_if(this->modelGameObjectList.begin(), this->modelGameObjectList.end(),
            [&tag](const std::shared_ptr<ModelGameObject>& current) { return current->getTag() == tag; }),
        this->modelGameObjectList.end());
}

std::shared_ptr<LightGameObject> GameObjectManager::getLightGameObjectByGUID(const std::string& guid) {
    const auto found = this->lightGameObjectByGuid.find(guid);
    return found != this->lightGameObjectByGuid.end() ? found->second : nullptr;
}

std::shared_ptr<LightGameObject> GameObjectManager::getLightGameObjectByName(const std::string& name) {
    for (const auto& current : this->lightGameObjectList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<LightGameObject> GameObjectManager::getLightGameObjectByTag(const std::string& tag) {
    for (const auto& current : this->lightGameObjectList) {
        if (current->getTag() == tag) {
            return current;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<LightGameObject>> GameObjectManager::getLightGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<LightGameObject>> result;
    for (const auto& current : this->lightGameObjectList) {
        if (current->getTag() == tag) {
            result.push_back(current);
        }
    }
    return result;
}

void GameObjectManager::removeLightGameObjectByGUID(const std::string& guid) {
    this->lightGameObjectByGuid.erase(guid);
    this->lightGameObjectList.erase(
        std::remove_if(this->lightGameObjectList.begin(), this->lightGameObjectList.end(),
            [&guid](const std::shared_ptr<LightGameObject>& current) { return current->getGUID() == guid; }),
        this->lightGameObjectList.end());
}

void GameObjectManager::removeLightGameObjectsByTag(const std::string& tag) {
    for (const auto& current : this->lightGameObjectList) {
        if (current->getTag() == tag) {
            this->lightGameObjectByGuid.erase(current->getGUID());
        }
    }
    this->lightGameObjectList.erase(
        std::remove_if(this->lightGameObjectList.begin(), this->lightGameObjectList.end(),
            [&tag](const std::shared_ptr<LightGameObject>& current) { return current->getTag() == tag; }),
        this->lightGameObjectList.end());
}
