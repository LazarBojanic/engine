#pragma once
#include "Util.hpp"

class Light {
private:
    std::string guid;
    std::string name;
public:
    glm::vec4 albedo;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    Light();
    Light(glm::vec4 albedo,  glm::vec3 ambient,  glm::vec3 diffuse, glm::vec3 specular);
    Light(const std::string& name, glm::vec4 albedo,  glm::vec3 ambient,  glm::vec3 diffuse, glm::vec3 specular);
    ~Light();

    const std::string& getGUID() {
        return this->guid;
    }
    const std::string& getName() {
        return this->name;
    }
};

