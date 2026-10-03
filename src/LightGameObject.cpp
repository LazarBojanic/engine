#include "LightGameObject.hpp"

LightGameObject::LightGameObject()
    : lightDrawData(std::make_shared<LightDrawData>()), isHit(false) {
    this->guid = Util::generateGUID();
}

LightGameObject::LightGameObject(const std::string& name,
	const std::string& tag,
	std::shared_ptr<LightDrawData> lightDrawData,
	float positionX, float positionY, float positionZ,
	float sizeX, float sizeY, float sizeZ,
	float scaleX, float scaleY, float scaleZ,
	float rotationX, float rotationY, float rotationZ,
	float speedX, float speedY, float speedZ,
	bool isHit)
    : guid(Util::generateGUID()), name(name), tag(tag), lightDrawData(std::move(lightDrawData)),
      speed(glm::vec3(speedX, speedY, speedZ)), isHit(isHit) {
    this->transform.setPosition(glm::vec3(positionX, positionY, positionZ));
    this->transform.setSize(glm::vec3(sizeX, sizeY, sizeZ));
    this->transform.setScale(glm::vec3(scaleX, scaleY, scaleZ));
    this->transform.setRotation(glm::vec3(rotationX, rotationY, rotationZ));
}

LightGameObject::~LightGameObject() {
}
