#pragma once

#include "Geometry.hpp"
#include "Util.hpp"

class Mesh {
private:
	std::string guid;
	std::string name;
	std::vector<std::shared_ptr<Geometry>> geometryList;
	mutable glm::vec3 localMin{ 0.0f };
	mutable glm::vec3 localMax{ 0.0f };
	mutable bool boundsDirty{ true };

	void computeLocalBounds() const;

public:
	Mesh();
	Mesh(const std::string& name);
	Mesh(const std::string& name, std::shared_ptr<Geometry> singleGeometry);
	Mesh(const std::string& name, std::vector<std::shared_ptr<Geometry>> geometryList);
	~Mesh();

	const std::string& getGUID() const {
		return this->guid;
	}

	const std::string& getName() const {
		return this->name;
	}

	void setName(const std::string& name) {
		this->name = name;
	}

	const std::vector<std::shared_ptr<Geometry>>& getGeometryList() const {
		return this->geometryList;
	}

	void setGeometryList(const std::vector<std::shared_ptr<Geometry>>& geometryList) {
		this->geometryList = geometryList;
		this->boundsDirty = true;
	}

	const glm::vec3& getLocalMin() const {
		if (this->boundsDirty) {
			this->computeLocalBounds();
		}
		return this->localMin;
	}

	const glm::vec3& getLocalMax() const {
		if (this->boundsDirty) {
			this->computeLocalBounds();
		}
		return this->localMax;
	}
};
