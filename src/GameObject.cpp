#include "GameObject.hpp"

#include "LightGameObject.hpp"

GameObject::GameObject(){
	this->guid = Util::generateGUID();
	this->name = "";
	this->tag = "";
	this->drawData = std::make_shared<DrawData>();
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

GameObject::GameObject(const std::string& name, const std::string& tag, std::shared_ptr<DrawData> drawData, float positionX, float positionY, float positionZ, float sizeX, float sizeY, float sizeZ, float scaleX, float scaleY, float scaleZ, float rotationX, float rotationY, float rotationZ, float speedX, float speedY, float speedZ, bool isHit){
	this->guid = Util::generateGUID();
	this->name = name;
	this->tag = tag;
	this->drawData = drawData;
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

GameObject::~GameObject(){

}

void GameObject::updateShaderUseTexture() {
	if (this->drawData->getShaderPhong() != nullptr) {
		this->drawData->getShaderPhong()->bind();
		this->drawData->getShaderPhong()->setBool("useTextureAlbedo", this->drawData->getUseTextureAlbedo());
		this->drawData->getShaderPhong()->setBool("useTextureDiffuse", this->drawData->getUseTextureDiffuse());
		this->drawData->getShaderPhong()->setBool("useTextureSpecular", this->drawData->getUseTextureSpecular());
		this->drawData->getShaderPhong()->setBool("useTextureNormal", this->drawData->getUseTextureNormal());
		this->drawData->getShaderPhong()->setBool("useTextureHeight", this->drawData->getUseTextureHeight());
		this->drawData->getShaderPhong()->setBool("useTextureRoughness", this->drawData->getUseTextureRoughness());
		this->drawData->getShaderPhong()->setBool("useTextureShininess", this->drawData->getUseTextureShininess());
		this->drawData->getShaderPhong()->setBool("useTextureMetalness", this->drawData->getUseTextureMetalness());
		this->drawData->getShaderPhong()->setBool("useTextureAmbientOcclusion", this->drawData->getUseTextureAmbientOcclusion());
	}
	if (this->drawData->getShaderPbr() != nullptr) {
		this->drawData->getShaderPbr()->bind();
		this->drawData->getShaderPbr()->setBool("useTextureAlbedo", this->drawData->getUseTextureAlbedo());
		this->drawData->getShaderPbr()->setBool("useTextureDiffuse", this->drawData->getUseTextureDiffuse());
		this->drawData->getShaderPbr()->setBool("useTextureSpecular", this->drawData->getUseTextureSpecular());
		this->drawData->getShaderPbr()->setBool("useTextureNormal", this->drawData->getUseTextureNormal());
		this->drawData->getShaderPbr()->setBool("useTextureHeight", this->drawData->getUseTextureHeight());
		this->drawData->getShaderPbr()->setBool("useTextureRoughness", this->drawData->getUseTextureRoughness());
		this->drawData->getShaderPbr()->setBool("useTextureShininess", this->drawData->getUseTextureShininess());
		this->drawData->getShaderPbr()->setBool("useTextureMetalness", this->drawData->getUseTextureMetalness());
		this->drawData->getShaderPbr()->setBool("useTextureAmbientOcclusion", this->drawData->getUseTextureAmbientOcclusion());
	}
}

void GameObject::updateShaderTime(float t) {
	if (this->drawData->getShaderPhong() != nullptr && this->drawData->getShadingType() == SHADING_TYPE::PHONG) {
		this->drawData->getShaderPhong()->bind();
		this->drawData->getShaderPhong()->setFloat("uTime", t);
	}
	if (this->drawData->getShaderPbr() != nullptr && this->drawData->getShadingType() == SHADING_TYPE::PBR) {
		this->drawData->getShaderPbr()->bind();
		this->drawData->getShaderPbr()->setFloat("uTime", t);
	}
}

void GameObject::updateShaderMaterial() {
	if (this->drawData->getMaterial() != nullptr) {
		if (this->drawData->getShaderPhong() != nullptr && this->drawData->getShadingType() == SHADING_TYPE::PHONG) {
			this->drawData->getShaderPhong()->bind();
			this->drawData->getShaderPhong()->setVector4f("uMaterial.albedo", this->drawData->getMaterial()->albedo);
			this->drawData->getShaderPhong()->setVector3f("uMaterial.ambient", this->drawData->getMaterial()->ambient);
			this->drawData->getShaderPhong()->setVector3f("uMaterial.diffuse", this->drawData->getMaterial()->diffuse);
			this->drawData->getShaderPhong()->setVector3f("uMaterial.specular", this->drawData->getMaterial()->specular);
			this->drawData->getShaderPhong()->setFloat("uMaterial.shininess", this->drawData->getMaterial()->shininess);
		}
		if (this->drawData->getShaderPbr() != nullptr && this->drawData->getShadingType() == SHADING_TYPE::PBR) {
			this->drawData->getShaderPbr()->bind();
			this->drawData->getShaderPbr()->setVector4f("uMaterial.albedo", this->drawData->getMaterial()->albedo);
			this->drawData->getShaderPbr()->setVector3f("uMaterial.ambient", this->drawData->getMaterial()->ambient);
			this->drawData->getShaderPbr()->setVector3f("uMaterial.diffuse", this->drawData->getMaterial()->diffuse);
			this->drawData->getShaderPbr()->setVector3f("uMaterial.specular", this->drawData->getMaterial()->specular);
			this->drawData->getShaderPbr()->setFloat("uMaterial.shininess", this->drawData->getMaterial()->shininess);
		}
	}
}

void GameObject::updateShaderLight(std::shared_ptr<LightGameObject> lightGameObject) {

	if (this->drawData->getShaderPhong() != nullptr && this->drawData->getShadingType() == SHADING_TYPE::PHONG) {
		this->drawData->getShaderPhong()->bind();
		this->drawData->getShaderPhong()->setVector3f("uLight.position", glm::vec3(lightGameObject->getPositionX(), lightGameObject->getPositionY(), lightGameObject->getPositionZ()));
		this->drawData->getShaderPhong()->setVector4f("uLight.color", glm::vec4(lightGameObject->getLightDrawData()->getLight()->albedo.r, lightGameObject->getLightDrawData()->getLight()->albedo.g, lightGameObject->getLightDrawData()->getLight()->albedo.b, lightGameObject->getLightDrawData()->getLight()->albedo.a));
		this->drawData->getShaderPhong()->setVector3f("uLight.ambient", glm::vec3(lightGameObject->getLightDrawData()->getLight()->ambient.r, lightGameObject->getLightDrawData()->getLight()->ambient.g, lightGameObject->getLightDrawData()->getLight()->ambient.b));
		this->drawData->getShaderPhong()->setVector3f("uLight.diffuse", glm::vec3(lightGameObject->getLightDrawData()->getLight()->diffuse.r, lightGameObject->getLightDrawData()->getLight()->diffuse.g, lightGameObject->getLightDrawData()->getLight()->diffuse.b));
		this->drawData->getShaderPhong()->setVector3f("uLight.specular", glm::vec3(lightGameObject->getLightDrawData()->getLight()->specular.r, lightGameObject->getLightDrawData()->getLight()->specular.g, lightGameObject->getLightDrawData()->getLight()->specular.b));
	}
	if (this->drawData->getShaderPbr() != nullptr && this->drawData->getShadingType() == SHADING_TYPE::PBR) {
		this->drawData->getShaderPbr()->bind();
		this->drawData->getShaderPbr()->setVector3f("uLight.position", glm::vec3(lightGameObject->getPositionX(), lightGameObject->getPositionY(), lightGameObject->getPositionZ()));
		this->drawData->getShaderPbr()->setVector4f("uLight.color", glm::vec4(lightGameObject->getLightDrawData()->getLight()->albedo.r, lightGameObject->getLightDrawData()->getLight()->albedo.g, lightGameObject->getLightDrawData()->getLight()->albedo.b, lightGameObject->getLightDrawData()->getLight()->albedo.a));
		this->drawData->getShaderPbr()->setVector3f("uLight.ambient", glm::vec3(lightGameObject->getLightDrawData()->getLight()->ambient.r, lightGameObject->getLightDrawData()->getLight()->ambient.g, lightGameObject->getLightDrawData()->getLight()->ambient.b));
		this->drawData->getShaderPbr()->setVector3f("uLight.diffuse", glm::vec3(lightGameObject->getLightDrawData()->getLight()->diffuse.r, lightGameObject->getLightDrawData()->getLight()->diffuse.g, lightGameObject->getLightDrawData()->getLight()->diffuse.b));
		this->drawData->getShaderPbr()->setVector3f("uLight.specular", glm::vec3(lightGameObject->getLightDrawData()->getLight()->specular.r, lightGameObject->getLightDrawData()->getLight()->specular.g, lightGameObject->getLightDrawData()->getLight()->specular.b));
	}
}

void GameObject::updateShaderViewData(glm::mat4 modelMatrix, glm::mat4 inverseModelMatrix, glm::mat4 viewMatrix,  glm::mat4 projectionMatrix, glm::vec3 viewPos) {
	if (this->drawData->getShaderPhong() != nullptr && this->drawData->getShadingType() == SHADING_TYPE::PHONG) {
		this->drawData->getShaderPhong()->bind();
		this->drawData->getShaderPhong()->setMatrix4f("uModel", modelMatrix);
		this->drawData->getShaderPhong()->setMatrix4f("uInverseModel", inverseModelMatrix);
		this->drawData->getShaderPhong()->setMatrix4f("uView", viewMatrix);
		this->drawData->getShaderPhong()->setMatrix4f("uProjection", projectionMatrix);
		this->drawData->getShaderPhong()->setVector3f("uViewPos", viewPos);
	}
	if (this->drawData->getShaderPbr() != nullptr && this->drawData->getShadingType() == SHADING_TYPE::PBR) {
		this->drawData->getShaderPbr()->bind();
		this->drawData->getShaderPbr()->setMatrix4f("uModel", modelMatrix);
		this->drawData->getShaderPbr()->setMatrix4f("uInverseModel", inverseModelMatrix);
		this->drawData->getShaderPbr()->setMatrix4f("uView", viewMatrix);
		this->drawData->getShaderPbr()->setMatrix4f("uProjection", projectionMatrix);
		this->drawData->getShaderPbr()->setVector3f("uViewPos", viewPos);
	}
}