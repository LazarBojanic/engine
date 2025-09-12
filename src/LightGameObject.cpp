#include "LightGameObject.hpp"

LightGameObject::LightGameObject(){
	this->guid = Util::generateGUID();
	this->name = "";
	this->tag = "";
	this->lightDrawData = std::make_shared<LightDrawData>();
	this->positionX = 0.0f;
	this->positionY = 0.0f;
	this->positionZ = 0.0f;
	this->sizeX = 1.0f;
	this->sizeY = 1.0f;
	this->sizeZ = 1.0f;
	this->scaleX = 1.0f;
	this->scaleY = 1.0f;
	this->scaleZ = 1.0f;
	this->scaledSizeX = 1.0f;
	this->scaledSizeY = 1.0f;
	this->scaledSizeZ = 1.0f;
	this->rotationX = 0.0f;
	this->rotationY = 0.0f;
	this->rotationZ = 0.0f;
	this->speedX = 0.0f;
	this->speedY = 0.0f;
	this->speedZ = 0.0f;
	this->isHit = false;
}

LightGameObject::LightGameObject(const std::string& name,
				const std::string& tag,
				std::shared_ptr<LightDrawData> lightDrawData,
				float positionX, float positionY, float positionZ,
				float sizeX, float sizeY, float sizeZ,
				float scaleX, float scaleY, float scaleZ,
				float rotationX, float rotationY, float rotationZ,
				float speedX, float speedY, float speedZ,
				bool isHit){
	this->guid = Util::generateGUID();
	this->name = name;
	this->tag = tag;
	this->lightDrawData = lightDrawData;
	this->positionX = positionX;
	this->positionY = positionY;
	this->positionZ = positionZ;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->sizeZ = sizeZ;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
	this->scaledSizeX = this->sizeX * this->scaleX;
	this->scaledSizeY = this->sizeY * this->scaleY;
	this->scaledSizeZ = this->sizeZ * this->scaleZ;
	this->rotationX = rotationX;
	this->rotationY = rotationY;
	this->rotationZ = rotationZ;
	this->speedX = speedX;
	this->speedY = speedY;
	this->speedZ = speedZ;
	this->isHit = isHit;
}

LightGameObject::~LightGameObject(){

}


void LightGameObject::updateShaderTime(float t) {
	if (this->lightDrawData->getShader() != nullptr) {
		this->lightDrawData->getShader()->bind();
		this->lightDrawData->getShader()->setFloat("uTime", t);
	}
}

void LightGameObject::updateShaderColor() {
	if (this->lightDrawData->getShader() != nullptr) {
		this->lightDrawData->getShader()->bind();
		this->lightDrawData->getShader()->setVector4f("uColor", this->lightDrawData->getLight()->albedo);
	}
}
void LightGameObject::updateShaderViewData(glm::mat4 modelMatrix, glm::mat4 inverseModelMatrix, glm::mat4 viewMatrix,  glm::mat4 projectionMatrix, glm::vec3 viewPos) {
	if (this->lightDrawData->getShader() != nullptr) {
		this->lightDrawData->getShader()->bind();
		this->lightDrawData->getShader()->setMatrix4f("uModel", modelMatrix);
		this->lightDrawData->getShader()->setMatrix4f("uInverseModel", inverseModelMatrix);
		this->lightDrawData->getShader()->setMatrix4f("uView", viewMatrix);
		this->lightDrawData->getShader()->setMatrix4f("uProjection", projectionMatrix);
		this->lightDrawData->getShader()->setVector3f("uViewPos", viewPos);
	}
}