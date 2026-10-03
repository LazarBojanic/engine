#pragma once

#include "Util.hpp"
#include "DrawData.hpp"
#include "Transform.hpp"

class GameObject {
private:
	std::string guid;
	std::string name;
	std::string tag;
	std::shared_ptr<DrawData> drawData;
	Transform transform;
	glm::vec3 speed{ 0.0f };
	bool isHit;

public:
	GameObject();
	GameObject(const std::string& name, const std::string& tag, std::shared_ptr<DrawData> drawData,
		float positionX, float positionY, float positionZ,
		float sizeX, float sizeY, float sizeZ,
		float scaleX, float scaleY, float scaleZ,
		float rotationX, float rotationY, float rotationZ,
		float speedX, float speedY, float speedZ,
		bool isHit);
	~GameObject();

	const std::string& getGUID() const {
		return this->guid;
	}

	const std::string& getName() const {
		return this->name;
	}

	const std::string& getTag() const {
		return this->tag;
	}

	const std::shared_ptr<DrawData>& getDrawData() const {
		return this->drawData;
	}

	Transform& getTransform() {
		return this->transform;
	}

	const Transform& getTransform() const {
		return this->transform;
	}

	float getSpeedX() const {
		return this->speed.x;
	}

	float getSpeedY() const {
		return this->speed.y;
	}

	float getSpeedZ() const {
		return this->speed.z;
	}

	bool getIsHit() const {
		return this->isHit;
	}

	void setName(const std::string& name) {
		this->name = name;
	}

	void setTag(const std::string& tag) {
		this->tag = tag;
	}

	void setSpeedX(float speedX) {
		this->speed.x = speedX;
	}

	void setSpeedY(float speedY) {
		this->speed.y = speedY;
	}

	void setSpeedZ(float speedZ) {
		this->speed.z = speedZ;
	}

	void setIsHit(bool isHit) {
		this->isHit = isHit;
	}
};
