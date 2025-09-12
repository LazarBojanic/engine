#include "GameObjectManager.hpp"

GameObjectManager* GameObjectManager::instance;

GameObjectManager::GameObjectManager() {
    this->gameObjectList = std::vector<std::shared_ptr<GameObject>>();
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
}

std::shared_ptr<GameObject> GameObjectManager::addGameObject(std::shared_ptr<GameObject> gameObject) {
    auto found = this->getGameObjectByGUID(gameObject->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->gameObjectList.push_back(gameObject);
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

    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name, tag, drawData, positionX, positionY, positionZ, sizeX,  sizeY, sizeZ, scaleX, scaleY, scaleZ, rotationX,  rotationY, rotationZ, speedX, speedY, speedZ, isHit);

    auto found = this->getGameObjectByGUID(gameObject->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->gameObjectList.push_back(gameObject);
    return this->gameObjectList.back();
}

std::shared_ptr<ModelGameObject> GameObjectManager::addModelGameObject(std::shared_ptr<ModelGameObject> modelGameObject) {
    auto found = this->getModelGameObjectByGUID(modelGameObject->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->modelGameObjectList.push_back(modelGameObject);
    return this->modelGameObjectList.back();
}

std::shared_ptr<ModelGameObject> GameObjectManager::addModelGameObject(const std::string& name, const std::string& tag, std::shared_ptr<ModelDrawData> modelDrawData,
    float positionX, float positionY, float positionZ,
    float sizeX, float sizeY, float sizeZ,
    float scaleX, float scaleY, float scaleZ,
    float rotationX, float rotationY, float rotationZ,
    float speedX, float speedY, float speedZ,
    bool isHit) {

    std::shared_ptr<ModelGameObject> modelGameObject = std::make_shared<ModelGameObject>(name, tag, modelDrawData,
        positionX, positionY, positionZ,
        sizeX, sizeY, sizeZ,
        scaleX, scaleY, scaleZ,
        rotationX, rotationY, rotationZ,
        speedX, speedY, speedZ,
        isHit);

    auto found = this->getModelGameObjectByGUID(modelGameObject->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->modelGameObjectList.push_back(modelGameObject);
    return this->modelGameObjectList.back();

}

std::shared_ptr<LightGameObject> GameObjectManager::addLightGameObject(std::shared_ptr<LightGameObject> lightGameObject) {
    auto found = this->getLightGameObjectByGUID(lightGameObject->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->lightGameObjectList.push_back(lightGameObject);
    return this->lightGameObjectList.back();
}

std::shared_ptr<LightGameObject> GameObjectManager::addLightGameObject(const std::string& name, const std::string& tag, std::shared_ptr<LightDrawData> lightDrawData,
    float positionX, float positionY, float positionZ,
    float sizeX, float sizeY, float sizeZ,
    float scaleX, float scaleY, float scaleZ,
    float rotationX, float rotationY, float rotationZ,
    float speedX, float speedY, float speedZ,
    bool isHit) {

    std::shared_ptr<LightGameObject> lightGameObject = std::make_shared<LightGameObject>(name, tag, lightDrawData,
        positionX, positionY, positionZ,
        sizeX, sizeY, sizeZ,
        scaleX, scaleY, scaleZ,
        rotationX, rotationY, rotationZ,
        speedX, speedY, speedZ,
        isHit);

    auto found = this->getLightGameObjectByGUID(lightGameObject->getGUID());
    if (found != nullptr) {
        return found;
    }
    this->lightGameObjectList.push_back(lightGameObject);
    return this->lightGameObjectList.back();

}

std::shared_ptr<GameObject> GameObjectManager::getGameObjectByGUID(const std::string& guid) {
    for (auto current : this->gameObjectList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<GameObject> GameObjectManager::getGameObjectByName(const std::string& name) {
    for (auto current : this->gameObjectList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<GameObject> GameObjectManager::getGameObjectByTag(const std::string& tag) {
    for (auto current : this->gameObjectList) {
        if (current->getTag() == tag) {
            return current;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<GameObject>> GameObjectManager::getGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<GameObject>> gameObjectsList = std::vector<std::shared_ptr<GameObject>>();
    for (auto current : this->gameObjectList) {
        if (current->getTag() == tag) {
            gameObjectsList.push_back(current);
        }
    }
    return gameObjectsList;
}

void GameObjectManager::removeGameObjectByGUID(const std::string& guid) {
    std::vector<std::shared_ptr<GameObject>> tempGameObjectList = std::vector<std::shared_ptr<GameObject>>();
    for (auto current : this->gameObjectList) {
        if (current->getGUID() != guid) {
            tempGameObjectList.push_back(current);
        }
    }
    this->gameObjectList = tempGameObjectList;
}

void GameObjectManager::removeGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<GameObject>> tempGameObjectList = std::vector<std::shared_ptr<GameObject>>();
    for (auto current : this->gameObjectList) {
        if (current->getTag() != tag) {
            tempGameObjectList.push_back(current);
        }
    }
    this->gameObjectList = tempGameObjectList;
}

std::shared_ptr<ModelGameObject> GameObjectManager::getModelGameObjectByGUID(const std::string& guid) {
    for (auto current : this->modelGameObjectList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<ModelGameObject> GameObjectManager::getModelGameObjectByName(const std::string& name) {
    for (auto current : this->modelGameObjectList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<ModelGameObject> GameObjectManager::getModelGameObjectByTag(const std::string& tag) {
    for (auto current : this->modelGameObjectList) {
        if (current->getTag() == tag) {
            return current;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<ModelGameObject>> GameObjectManager::getModelGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<ModelGameObject>> modelGameObjectList = std::vector<std::shared_ptr<ModelGameObject>>();
    for (auto current : this->modelGameObjectList) {
        if (current->getTag() == tag) {
            modelGameObjectList.push_back(current);
        }
    }
    return modelGameObjectList;
}

void GameObjectManager::removeModelGameObjectByGUID(const std::string& guid) {
    std::vector<std::shared_ptr<ModelGameObject>> tempModelGameObjectList = std::vector<std::shared_ptr<ModelGameObject>>();
    for (auto current : this->modelGameObjectList) {
        if (current->getGUID() != guid) {
            tempModelGameObjectList.push_back(current);
        }
    }
    this->modelGameObjectList = tempModelGameObjectList;
}

void GameObjectManager::removeModelGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<ModelGameObject>> tempModelGameObjectList = std::vector<std::shared_ptr<ModelGameObject>>();
    for (auto current : this->modelGameObjectList) {
        if (current->getTag() != tag) {
            tempModelGameObjectList.push_back(current);
        }
    }
    this->modelGameObjectList = tempModelGameObjectList;
}

std::shared_ptr<LightGameObject> GameObjectManager::getLightGameObjectByGUID(const std::string& guid) {
    for (auto current : this->lightGameObjectList) {
        if (current->getGUID() == guid) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<LightGameObject> GameObjectManager::getLightGameObjectByName(const std::string& name) {
    for (auto current : this->lightGameObjectList) {
        if (current->getName() == name) {
            return current;
        }
    }
    return nullptr;
}

std::shared_ptr<LightGameObject> GameObjectManager::getLightGameObjectByTag(const std::string& tag) {
    for (auto current : this->lightGameObjectList) {
        if (current->getTag() == tag) {
            return current;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<LightGameObject>> GameObjectManager::getLightGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<LightGameObject>> lightGameObjectList = std::vector<std::shared_ptr<LightGameObject>>();
    for (auto current : this->lightGameObjectList) {
        if (current->getTag() == tag) {
            lightGameObjectList.push_back(current);
        }
    }
    return lightGameObjectList;
}

void GameObjectManager::removeLightGameObjectByGUID(const std::string& guid) {
    std::vector<std::shared_ptr<LightGameObject>> tempLightGameObjectList = std::vector<std::shared_ptr<LightGameObject>>();
    for (auto current : this->lightGameObjectList) {
        if (current->getGUID() != guid) {
            tempLightGameObjectList.push_back(current);
        }
    }
    this->lightGameObjectList = tempLightGameObjectList;
}

void GameObjectManager::removeLightGameObjectsByTag(const std::string& tag) {
    std::vector<std::shared_ptr<LightGameObject>> tempLightGameObjectList = std::vector<std::shared_ptr<LightGameObject>>();
    for (auto current : this->lightGameObjectList) {
        if (current->getName() != tag) {
            tempLightGameObjectList.push_back(current);
        }
    }
    this->lightGameObjectList = tempLightGameObjectList;
}

