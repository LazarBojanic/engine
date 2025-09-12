#include "ModelGameObject.hpp"

ModelGameObject::ModelGameObject(){
	this->guid = Util::generateGUID();
	this->name = "";
	this->tag = "";
	this->modelDrawData = std::make_shared<ModelDrawData>();
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

ModelGameObject::ModelGameObject(const std::string& name, const std::string& tag, std::shared_ptr<ModelDrawData> modelDrawData,
					float positionX, float positionY, float positionZ,
					float sizeX, float sizeY, float sizeZ,
					float scaleX, float scaleY, float scaleZ,
					float rotationX, float rotationY, float rotationZ,
					float speedX, float speedY, float speedZ,
					bool isHit){
	this->guid = Util::generateGUID();
	this->name = name;
	this->tag = tag;
	this->modelDrawData = modelDrawData;
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

ModelGameObject::~ModelGameObject(){

}

void ModelGameObject::updateShaderUseTexture() {
	if (this->modelDrawData->getShaderPhong() != nullptr) {
		this->modelDrawData->getShaderPhong()->bind();
		this->modelDrawData->getShaderPhong()->setBool("useTextureAlbedo", this->modelDrawData->getUseTextureAlbedo());
		this->modelDrawData->getShaderPhong()->setBool("useTextureDiffuse", this->modelDrawData->getUseTextureDiffuse());
		this->modelDrawData->getShaderPhong()->setBool("useTextureSpecular", this->modelDrawData->getUseTextureSpecular());
		this->modelDrawData->getShaderPhong()->setBool("useTextureNormal", this->modelDrawData->getUseTextureNormal());
		this->modelDrawData->getShaderPhong()->setBool("useTextureHeight", this->modelDrawData->getUseTextureHeight());
		this->modelDrawData->getShaderPhong()->setBool("useTextureRoughness", this->modelDrawData->getUseTextureRoughness());
		this->modelDrawData->getShaderPhong()->setBool("useTextureShininess", this->modelDrawData->getUseTextureShininess());
		this->modelDrawData->getShaderPhong()->setBool("useTextureMetalness", this->modelDrawData->getUseTextureMetalness());
		this->modelDrawData->getShaderPhong()->setBool("useTextureAmbientOcclusion", this->modelDrawData->getUseTextureAmbientOcclusion());
	}
	if (this->modelDrawData->getShaderPbr() != nullptr) {
		this->modelDrawData->getShaderPbr()->bind();
		this->modelDrawData->getShaderPbr()->setBool("useTextureAlbedo", this->modelDrawData->getUseTextureAlbedo());
		this->modelDrawData->getShaderPbr()->setBool("useTextureDiffuse", this->modelDrawData->getUseTextureDiffuse());
		this->modelDrawData->getShaderPbr()->setBool("useTextureSpecular", this->modelDrawData->getUseTextureSpecular());
		this->modelDrawData->getShaderPbr()->setBool("useTextureNormal", this->modelDrawData->getUseTextureNormal());
		this->modelDrawData->getShaderPbr()->setBool("useTextureHeight", this->modelDrawData->getUseTextureHeight());
		this->modelDrawData->getShaderPbr()->setBool("useTextureRoughness", this->modelDrawData->getUseTextureRoughness());
		this->modelDrawData->getShaderPbr()->setBool("useTextureShininess", this->modelDrawData->getUseTextureShininess());
		this->modelDrawData->getShaderPbr()->setBool("useTextureMetalness", this->modelDrawData->getUseTextureMetalness());
		this->modelDrawData->getShaderPbr()->setBool("useTextureAmbientOcclusion", this->modelDrawData->getUseTextureAmbientOcclusion());
	}
}

void ModelGameObject::updateShaderTime(float t) {
	if (this->modelDrawData->getShaderPhong() != nullptr && this->modelDrawData->getShadingType() == SHADING_TYPE::PHONG) {
		this->modelDrawData->getShaderPhong()->bind();
		this->modelDrawData->getShaderPhong()->setFloat("uTime", t);
	}
	if (this->modelDrawData->getShaderPbr() != nullptr && this->modelDrawData->getShadingType() == SHADING_TYPE::PBR) {
		this->modelDrawData->getShaderPbr()->bind();
		this->modelDrawData->getShaderPbr()->setFloat("uTime", t);
	}
}

void ModelGameObject::updateShaderMaterial() {
	if (this->modelDrawData->getMaterial() != nullptr) {
		if (this->modelDrawData->getShaderPhong() != nullptr && this->modelDrawData->getShadingType() == SHADING_TYPE::PHONG) {
			this->modelDrawData->getShaderPhong()->bind();
			this->modelDrawData->getShaderPhong()->setVector4f("uMaterial.albedo", this->modelDrawData->getMaterial()->albedo);
			this->modelDrawData->getShaderPhong()->setVector3f("uMaterial.ambient", this->modelDrawData->getMaterial()->ambient);
			this->modelDrawData->getShaderPhong()->setVector3f("uMaterial.diffuse", this->modelDrawData->getMaterial()->diffuse);
			this->modelDrawData->getShaderPhong()->setVector3f("uMaterial.specular", this->modelDrawData->getMaterial()->specular);
			this->modelDrawData->getShaderPhong()->setFloat("uMaterial.shininess", this->modelDrawData->getMaterial()->shininess);
		}
		if (this->modelDrawData->getShaderPbr() != nullptr && this->modelDrawData->getShadingType() == SHADING_TYPE::PBR) {
			this->modelDrawData->getShaderPbr()->bind();
			this->modelDrawData->getShaderPbr()->setVector4f("uMaterial.albedo", this->modelDrawData->getMaterial()->albedo);
			this->modelDrawData->getShaderPbr()->setVector3f("uMaterial.ambient", this->modelDrawData->getMaterial()->ambient);
			this->modelDrawData->getShaderPbr()->setVector3f("uMaterial.diffuse", this->modelDrawData->getMaterial()->diffuse);
			this->modelDrawData->getShaderPbr()->setVector3f("uMaterial.specular", this->modelDrawData->getMaterial()->specular);
			this->modelDrawData->getShaderPbr()->setFloat("uMaterial.shininess", this->modelDrawData->getMaterial()->shininess);
		}
	}
}
void ModelGameObject::updateShaderLight(std::shared_ptr<LightGameObject> lightGameObject) {

	if (this->modelDrawData->getShaderPhong() != nullptr && this->modelDrawData->getShadingType() == SHADING_TYPE::PHONG) {
		this->modelDrawData->getShaderPhong()->bind();
		this->modelDrawData->getShaderPhong()->setVector3f("uLight.position", glm::vec3(lightGameObject->getPositionX(), lightGameObject->getPositionY(), lightGameObject->getPositionZ()));
		this->modelDrawData->getShaderPhong()->setVector4f("uLight.color", glm::vec4(lightGameObject->getLightDrawData()->getLight()->albedo.r, lightGameObject->getLightDrawData()->getLight()->albedo.g, lightGameObject->getLightDrawData()->getLight()->albedo.b, lightGameObject->getLightDrawData()->getLight()->albedo.a));
		this->modelDrawData->getShaderPhong()->setVector3f("uLight.ambient", glm::vec3(lightGameObject->getLightDrawData()->getLight()->ambient.r, lightGameObject->getLightDrawData()->getLight()->ambient.g, lightGameObject->getLightDrawData()->getLight()->ambient.b));
		this->modelDrawData->getShaderPhong()->setVector3f("uLight.diffuse", glm::vec3(lightGameObject->getLightDrawData()->getLight()->diffuse.r, lightGameObject->getLightDrawData()->getLight()->diffuse.g, lightGameObject->getLightDrawData()->getLight()->diffuse.b));
		this->modelDrawData->getShaderPhong()->setVector3f("uLight.specular", glm::vec3(lightGameObject->getLightDrawData()->getLight()->specular.r, lightGameObject->getLightDrawData()->getLight()->specular.g, lightGameObject->getLightDrawData()->getLight()->specular.b));
	}
	if (this->modelDrawData->getShaderPbr() != nullptr && this->modelDrawData->getShadingType() == SHADING_TYPE::PBR) {
		this->modelDrawData->getShaderPbr()->bind();
		this->modelDrawData->getShaderPbr()->setVector3f("uLight.position", glm::vec3(lightGameObject->getPositionX(), lightGameObject->getPositionY(), lightGameObject->getPositionZ()));
		this->modelDrawData->getShaderPbr()->setVector4f("uLight.color", glm::vec4(lightGameObject->getLightDrawData()->getLight()->albedo.r, lightGameObject->getLightDrawData()->getLight()->albedo.g, lightGameObject->getLightDrawData()->getLight()->albedo.b, lightGameObject->getLightDrawData()->getLight()->albedo.a));
		this->modelDrawData->getShaderPbr()->setVector3f("uLight.ambient", glm::vec3(lightGameObject->getLightDrawData()->getLight()->ambient.r, lightGameObject->getLightDrawData()->getLight()->ambient.g, lightGameObject->getLightDrawData()->getLight()->ambient.b));
		this->modelDrawData->getShaderPbr()->setVector3f("uLight.diffuse", glm::vec3(lightGameObject->getLightDrawData()->getLight()->diffuse.r, lightGameObject->getLightDrawData()->getLight()->diffuse.g, lightGameObject->getLightDrawData()->getLight()->diffuse.b));
		this->modelDrawData->getShaderPbr()->setVector3f("uLight.specular", glm::vec3(lightGameObject->getLightDrawData()->getLight()->specular.r, lightGameObject->getLightDrawData()->getLight()->specular.g, lightGameObject->getLightDrawData()->getLight()->specular.b));
	}
}
void ModelGameObject::updateShaderViewData(glm::mat4 modelMatrix, glm::mat4 inverseModelMatrix, glm::mat4 viewMatrix,  glm::mat4 projectionMatrix, glm::vec3 viewPos) {
	if (this->modelDrawData->getShaderPhong() != nullptr && this->modelDrawData->getShadingType() == SHADING_TYPE::PHONG) {
		this->modelDrawData->getShaderPhong()->bind();
		this->modelDrawData->getShaderPhong()->setMatrix4f("uModel", modelMatrix);
		this->modelDrawData->getShaderPhong()->setMatrix4f("uInverseModel", inverseModelMatrix);
		this->modelDrawData->getShaderPhong()->setMatrix4f("uView", viewMatrix);
		this->modelDrawData->getShaderPhong()->setMatrix4f("uProjection", projectionMatrix);
		this->modelDrawData->getShaderPhong()->setVector3f("uViewPos", viewPos);
	}
	if (this->modelDrawData->getShaderPbr() != nullptr && this->modelDrawData->getShadingType() == SHADING_TYPE::PBR) {
		this->modelDrawData->getShaderPbr()->bind();
		this->modelDrawData->getShaderPbr()->setMatrix4f("uModel", modelMatrix);
		this->modelDrawData->getShaderPbr()->setMatrix4f("uInverseModel", inverseModelMatrix);
		this->modelDrawData->getShaderPbr()->setMatrix4f("uView", viewMatrix);
		this->modelDrawData->getShaderPbr()->setMatrix4f("uProjection", projectionMatrix);
		this->modelDrawData->getShaderPbr()->setVector3f("uViewPos", viewPos);
	}
}