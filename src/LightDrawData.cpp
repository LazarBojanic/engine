#include "LightDrawData.hpp"

LightDrawData::LightDrawData() {
    this->guid = Util::generateGUID();
    this->name = "";
    this->light = std::make_shared<Light>();
    this->mesh = std::make_shared<Mesh>();
    this->shader = std::make_shared<Shader>();
}

LightDrawData::LightDrawData(const std::string& name, std::shared_ptr<Light> light, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->light = light;
    this->mesh = mesh;
    this->shader = shader;
}

LightDrawData::~LightDrawData() {

}
