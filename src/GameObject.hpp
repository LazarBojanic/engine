#pragma once

#include "Util.hpp"
#include "DrawData.hpp"
#include "LightGameObject.hpp"
#include "ModelDrawData.hpp"

class GameObject {
private:
	std::string guid;
	std::string name;
	std::string tag;
	std::shared_ptr<DrawData> drawData;
	float positionX, positionY, positionZ;
	float sizeX, sizeY, sizeZ;
	float scaleX, scaleY, scaleZ;
	float scaledSizeX, scaledSizeY, scaledSizeZ;
	float rotationX, rotationY, rotationZ;
	float speedX, speedY, speedZ;
	bool isHit;
public:
	GameObject();
	GameObject(const std::string& name, const std::string& tag, std::shared_ptr<DrawData> drawData, float positionX, float positionY, float positionZ, float sizeX, float sizeY, float sizeZ, float scaleX, float scaleY, float scaleZ, float rotationX, float rotationY, float rotationZ, float speedX, float speedY, float speedZ, bool isHit);
	~GameObject();
	void updateShaderUseTexture();
	void updateShaderTime(float t);
	void updateShaderMaterial();
	void updateShaderLight(std::shared_ptr<LightGameObject> lightGameObject);
	void updateShaderViewData(glm::mat4 modelMatrix, glm::mat4 inverseModelMatrix, glm::mat4 viewMatrix,  glm::mat4 projectionMatrix, glm::vec3 viewPos);
	std::string getGUID() {
		return this->guid;
	}
	std::string getName() {
		return this->name;
	}
	std::string getTag() {
		return this->tag;
	}
	std::shared_ptr<DrawData> getDrawData() {
		return this->drawData;
	}
	float getPositionX() {
		return this->positionX;
	}
	float getPositionY() {
		return this->positionY;
	}
	float getPositionZ() {
		return this->positionZ;
	}
	float getSizeX() {
		return this->sizeX;
	}
	float getSizeY() {
		return this->sizeY;
	}
	float getSizeZ() {
		return this->sizeZ;
	}
	float getScaleX() {
		return this->scaleX;
	}
	float getScaleY() {
		return this->scaleY;
	}
	float getScaleZ() {
		return this->scaleZ;
	}
	float getScaledSizeX() {
		return this->scaledSizeX;
	}
	float getScaledSizeY() {
		return this->scaledSizeY;
	}
	float getScaledSizeZ() {
		return this->scaledSizeZ;
	}
	float getRotationX() {
		return this->rotationX;
	}
	float getRotationY() {
		return this->rotationY;
	}
	float getRotationZ() {
		return this->rotationZ;
	}
	float getSpeedX() {
		return this->speedX;
	}
	float getSpeedY() {
		return this->speedY;
	}
	float getSpeedZ() {
		return this->speedZ;
	}
	bool getIsHit() {
		return this->isHit;
	}

	void setName(std::string name) {
		this->name = name;
	}
	void setTag(std::string tag) {
		this->tag = tag;
	}
	void setPositionX(float positionX) {
		this->positionX = positionX;
	}
	void setPositionY(float positionY) {
		this->positionY = positionY;
	}
	void setPositionZ(float positionZ) {
		this->positionZ = positionZ;
	}
	void setSizeX(float sizeX) {
		this->sizeX = sizeX;
		this->scaledSizeX = this->sizeX * this->scaleX;
	}
	void setSizeY(float sizeY) {
		this->sizeY = sizeY;
		this->scaledSizeY = this->sizeY * this->scaleY;
	}
	void setSizeZ(float sizeZ) {
		this->sizeZ = sizeZ;
		this->scaledSizeZ = this->sizeZ * this->scaleZ;
	}
	void setScaleX(float scaleX) {
		this->scaleX = scaleX;
		this->scaledSizeX = this->sizeX * this->scaleX;
	}
	void setScaleY(float scaleY) {
		this->scaleY = scaleY;
		this->scaledSizeY = this->sizeY * this->scaleY;
	}
	void setScaleZ(float scaleZ) {
		this->scaleZ = scaleZ;
		this->scaledSizeZ = this->sizeZ * this->scaleZ;
	}
	void setRotationX(float rotationX) {
		this->rotationX = rotationX;
	}
	void setRotationY(float rotationY) {
		this->rotationY = rotationY;
	}
	void setRotationZ(float rotationZ) {
		this->rotationZ = rotationZ;
	}
	void setSpeedX(float speedX) {
		this->speedX = speedX;
	}
	void setSpeedY(float speedY){
		this->speedY = speedY;
	}
	void setSpeedZ(float speedZ) {
		this->speedZ = speedZ;
	}
	void setIsHit(bool isHit) {
		this->isHit = isHit;
	}
};
