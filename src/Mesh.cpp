#include "Mesh.hpp"

#include <limits>

Mesh::Mesh() {
    this->guid = Util::generateGUID();
    this->name = "";
}

Mesh::Mesh(const std::string& name) {
    this->guid = Util::generateGUID();
    this->name = name;
}

Mesh::Mesh(const std::string& name, std::shared_ptr<Geometry> singleGeometry) {
    this->guid = Util::generateGUID();
    this->name = name;
    if (singleGeometry != nullptr) {
        this->geometryList.push_back(std::move(singleGeometry));
    }
}

Mesh::Mesh(const std::string& name, std::vector<std::shared_ptr<Geometry>> geometryList) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->geometryList = std::move(geometryList);
}

Mesh::~Mesh() {
}

void Mesh::computeLocalBounds() const {
    if (this->geometryList.empty()) {
        this->localMin = glm::vec3(0.0f);
        this->localMax = glm::vec3(0.0f);
        this->boundsDirty = false;
        return;
    }

    constexpr float maxFloat = std::numeric_limits<float>::max();
    glm::vec3 min(maxFloat);
    glm::vec3 max(-maxFloat);
    for (const auto& geometry : this->geometryList) {
        if (geometry == nullptr) {
            continue;
        }
        min = glm::min(min, geometry->getLocalAABBMin());
        max = glm::max(max, geometry->getLocalAABBMax());
    }
    this->localMin = min;
    this->localMax = max;
    this->boundsDirty = false;
}
