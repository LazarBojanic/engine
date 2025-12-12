#pragma once

#include "Util.hpp"
#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "ModelGameObject.hpp"

class GameObjectManager{
private:
	GameObjectManager();
	~GameObjectManager();
	static GameObjectManager* instance;
	std::vector<std::shared_ptr<GameObject>> gameObjectList;
	std::vector<std::shared_ptr<ModelGameObject>> modelGameObjectList;
	std::vector<std::shared_ptr<LightGameObject>> lightGameObjectList;
public:
	static GameObjectManager* getInstance();
	void clear(bool reinitialize);
	std::shared_ptr<GameObject> addGameObject(std::shared_ptr<GameObject> gameObject);
	std::shared_ptr<GameObject> addGameObject(const std::string& name, const std::string& tag,
	std::shared_ptr<DrawData> drawData,
	float positionX, float positionY, float positionZ,
	float sizeX, float sizeY, float sizeZ,
	float scaleX, float scaleY, float scaleZ,
	float rotationX, float rotationY, float rotationZ,
	float speedX, float speedY, float speedZ,
	bool isHit);
	std::shared_ptr<ModelGameObject> addModelGameObject(std::shared_ptr<ModelGameObject> modelGameObject);
	std::shared_ptr<ModelGameObject> addModelGameObject(	const std::string& name,
															const std::string& tag,
															std::shared_ptr<ModelDrawData> modelDrawData,
															float positionX, float positionY, float positionZ,
															float sizeX, float sizeY, float sizeZ,
															float scaleX, float scaleY, float scaleZ,
															float rotationX, float rotationY, float rotationZ,
															float speedX, float speedY, float speedZ,
															bool isHit);
	std::shared_ptr<LightGameObject> addLightGameObject(std::shared_ptr<LightGameObject> lightGameObject);
	std::shared_ptr<LightGameObject> addLightGameObject(const std::string& name,
														const std::string& tag,
														std::shared_ptr<LightDrawData> lightDrawData,
														float positionX, float positionY, float positionZ,
														float sizeX, float sizeY, float sizeZ,
														float scaleX, float scaleY, float scaleZ,
														float rotationX, float rotationY, float rotationZ,
														float speedX, float speedY, float speedZ,
														bool isHit);
	std::shared_ptr<GameObject> getGameObjectByGUID(const std::string& guid);
	std::shared_ptr<GameObject> getGameObjectByName(const std::string& name);
	std::shared_ptr<GameObject> getGameObjectByTag(const std::string& tag);
	std::vector<std::shared_ptr<GameObject>> getGameObjectsByTag(const std::string& tag);
	void removeGameObjectByGUID(const std::string& guid);
	void removeGameObjectsByTag(const std::string& tag);
	std::vector<std::shared_ptr<GameObject>> getGameObjectList() {
		return this->gameObjectList;
	}

	std::shared_ptr<ModelGameObject> getModelGameObjectByGUID(const std::string& guid);
	std::shared_ptr<ModelGameObject> getModelGameObjectByName(const std::string& name);
	std::shared_ptr<ModelGameObject> getModelGameObjectByTag(const std::string& tag);
	std::vector<std::shared_ptr<ModelGameObject>> getModelGameObjectsByTag(const std::string& tag);
	void removeModelGameObjectByGUID(const std::string& guid);
	void removeModelGameObjectsByTag(const std::string& tag);
	std::vector<std::shared_ptr<ModelGameObject>> getModelGameObjectList() {
		return this->modelGameObjectList;
	}



	std::shared_ptr<LightGameObject> getLightGameObjectByGUID(const std::string& guid);
	std::shared_ptr<LightGameObject> getLightGameObjectByName(const std::string& name);
	std::shared_ptr<LightGameObject> getLightGameObjectByTag(const std::string& tag);
	std::vector<std::shared_ptr<LightGameObject>> getLightGameObjectsByTag(const std::string& tag);
	void removeLightGameObjectByGUID(const std::string& guid);
	void removeLightGameObjectsByTag(const std::string& tag);
	std::vector<std::shared_ptr<LightGameObject>> getLightGameObjectList() {
		return this->lightGameObjectList;
	}


};

