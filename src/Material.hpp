#pragma once

#include "Util.hpp"

class Material{
private:
	std::string guid;
	std::string name;
public:
	glm::vec4 albedo;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	Material();
	Material(const std::string& name, glm::vec4 albedo, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);


	~Material();

	const std::string& getGUID() {
		return this->guid;
	}

	const std::string& getName() {
		return this->name;
	}
};