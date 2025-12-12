#include "Material.hpp"

Material::Material(){
	this->guid = Util::generateGUID();
	this->name = "";
	this->albedo = glm::vec4(1.0f);
	this->ambient = glm::vec3(0.1f);
	this->diffuse = glm::vec3(0.1f);
	this->specular = glm::vec3(0.1f);
	this->shininess = 0.1f;
}

Material::Material(const std::string& name, glm::vec4 albedo, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess){
	this->guid = Util::generateGUID();
	this->name = name;
	this->albedo = albedo;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}



Material::~Material(){
}
