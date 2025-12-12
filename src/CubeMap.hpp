#pragma once

#include "Util.hpp"
#include "stb/stb_image.h"

class CubeMap {
private:
	std::string guid;
	unsigned int cubeMapId;
	std::vector<std::string> facePaths;
	std::string name;
	unsigned int width;
	unsigned int height;
	unsigned int mode;
	unsigned int wrap_S;
	unsigned int wrap_T;
	unsigned int wrap_R;
	unsigned int filterMin;
	unsigned int filterMax;
	GLenum format;
public:
	CubeMap();
	CubeMap(const std::string& name, std::vector<std::string> facePaths);
	~CubeMap();

	void bind(unsigned int textureChannel);
	void unbind();
	void generate(std::vector<std::string> facePaths);

	const std::string& getGUID() {
		return this->guid;
	}
	unsigned int getCubeMapId() {
		return this->cubeMapId;
	}
	const std::vector<std::string>& getFacePaths() {
		return this->facePaths;
	}
	const std::string& getName() {
		return this->name;
	}
	unsigned int getWidth() {
		return this->width;
	}
	unsigned int getHeight() {
		return this->height;
	}
	unsigned int getWrap_S() {
		return this->wrap_S;
	}
	unsigned int getWrap_T() {
		return this->wrap_T;
	}
	unsigned int getWrap_R() {
		return this->wrap_R;
	}
	unsigned int getFilterMin() {
		return this->filterMin;
	}
	unsigned int getFilterMax() {
		return this->filterMax;
	}
	GLenum getFormat() {
		return this->format;
	}
	GLenum getMode() {
		return this->mode;
	}
};