#pragma once

#include "Util.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class LightDrawData {
private:
	std::string guid;
	std::string name;
	std::shared_ptr<Light> light;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Shader> shader;
public:
	LightDrawData();
	LightDrawData(const std::string& name, std::shared_ptr<Light> light, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader);
	~LightDrawData();

	const std::string& getGUID() {
		return this->guid;
	}

	const std::string& getName() {
		return this->name;
	}
	std::shared_ptr<Light> getLight() {
		return this->light;
	}

	std::shared_ptr<Mesh> getMesh() {
		return this->mesh;
	}

	std::shared_ptr<Shader> getShader() {
		return this->shader;
	}

};
