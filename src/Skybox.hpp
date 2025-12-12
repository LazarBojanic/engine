#pragma once

#include "Util.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "CubeMap.hpp"

class Skybox {
private:
	std::string guid;
	std::string name;
	float colorX, colorY, colorZ;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<CubeMap> cubeMap;

public:
	Skybox();
	Skybox(const std::string& name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<CubeMap> cubeMap);
	Skybox(const std::string& name, float colorX, float colorY, float colorZ, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<CubeMap> cubeMap);
	~Skybox();
	void updateShaderTime(float t);
	void updateShaderColor();
	float getColorX() {
		return this->colorX;
	}
	float getColorY() {
		return this->colorY;
	}
	float getColorZ() {
		return this->colorZ;
	}
	const std::string& getGUID() {
		return this->guid;
	}
	const std::string& getName() {
		return this->name;
	}
	std::shared_ptr<Mesh> getMesh() {
		return this->mesh;
	}
	std::shared_ptr<Shader> getShader() {
		return this->shader;
	}
	std::shared_ptr<CubeMap> getCubeMap() {
		return this->cubeMap;
	}

};