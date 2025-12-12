#include "Mesh.hpp"

Mesh::Mesh() {
    this->guid = Util::generateGUID();
    this->name = "";
    this->geometryList = std::vector<std::shared_ptr<Geometry>>();
}

Mesh::Mesh(const std::string& name) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->geometryList = std::vector<std::shared_ptr<Geometry>>();
}

Mesh::Mesh(const std::string& name, std::shared_ptr<Geometry> singleGeometry) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->geometryList = std::vector<std::shared_ptr<Geometry>>();
    this->geometryList.push_back(singleGeometry);
}

Mesh::Mesh(const std::string& name, std::vector<std::shared_ptr<Geometry>> geometryList) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->geometryList = geometryList;
}

Mesh::~Mesh() {
}


