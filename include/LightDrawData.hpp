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

	const std::string& getGUID() const {
		return this->guid;
	}

	const std::string& getName() const {
		return this->name;
	}
	const std::shared_ptr<Light>& getLight() const {
		return this->light;
	}

	const std::shared_ptr<Mesh>& getMesh() const {
		return this->mesh;
	}

	const std::shared_ptr<Shader>& getShader() const {
		return this->shader;
	}

};
