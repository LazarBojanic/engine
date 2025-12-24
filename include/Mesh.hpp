#pragma once

#include "Geometry.hpp"
#include "Util.hpp"

class Mesh {
private:
	std::string guid;
	std::string name;
	std::vector<std::shared_ptr<Geometry>> geometryList;

public:
	Mesh();
	Mesh(const std::string& name);
	Mesh(const std::string& name, std::shared_ptr<Geometry> singleGeometry);
	Mesh(const std::string& name, std::vector<std::shared_ptr<Geometry>> geometryList);
	~Mesh();

	std::string getGUID() {
		return this->guid;
	}

	std::string getName() {
		return this->name;
	}

	void setName(const std::string& name) {
		this->name = name;
	}

	std::vector<std::shared_ptr<Geometry>> getGeometryList() {
		return this->geometryList;
	}
	void setGeometryList(std::vector<std::shared_ptr<Geometry>> geometryList) {
		this->geometryList = geometryList;
	}
};
