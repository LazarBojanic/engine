#include "Skybox.hpp"

Skybox::Skybox() {
	this->name = "";
	this->mesh = std::make_shared<Mesh>();
	this->shader = std::make_shared<Shader>();;
	this->cubeMap = std::make_shared<CubeMap>();
}


Skybox::Skybox(const std::string& name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<CubeMap> cubeMap) {
	this->name = name;
	this->colorX = 1.0f;
	this->colorY = 1.0f;
	this->colorZ = 1.0f;
	this->mesh = mesh;
	this->shader = shader;
	this->cubeMap = cubeMap;
}
Skybox::Skybox(const std::string& name, float colorX, float colorY, float colorZ, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<CubeMap> cubeMap) {
	this->name = name;
	this->colorX = colorX;
	this->colorY = colorY;
	this->colorZ = colorZ;
	this->mesh = mesh;
	this->shader = shader;
	this->cubeMap = cubeMap;
}

Skybox::~Skybox() {
}


void Skybox::updateShaderTime(float t) {
	if (this->getShader() != nullptr) {
		this->getShader()->bind();
		this->getShader()->setFloat("uTime", t);
	}
}

void Skybox::updateShaderColor() {
	if (this->getShader() != nullptr) {
		this->getShader()->bind();
		this->getShader()->setVector4f("uColor", glm::vec4(this->colorX, this->colorY, this->colorZ, 1.0f));
	}
}
