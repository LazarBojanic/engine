
#include "Light.hpp"


Light::Light() {
    this->guid = Util::generateGUID();
    this->name = "";
    this->albedo = glm::vec4(1.0f);
    this->ambient = glm::vec3(1.0f);
    this->diffuse = glm::vec3(1.0f);
    this->specular = glm::vec3(1.0f);
}
Light::Light(glm::vec4 albedo,  glm::vec3 ambient,  glm::vec3 diffuse, glm::vec3 specular) {
    this->guid = Util::generateGUID();
    this->name = "";
    this->albedo = albedo;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}
Light::Light(const std::string& name, glm::vec4 albedo,  glm::vec3 ambient,  glm::vec3 diffuse, glm::vec3 specular) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->albedo = albedo;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}
Light::~Light() {

}