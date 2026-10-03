#pragma once

#include "Util.hpp"
#include <cstddef>

struct InstanceData {
	glm::mat4 model{ 1.0f };
	glm::mat4 inverseModel{ 1.0f };
};

class InstanceBuffer {
private:
	unsigned int vboID;

public:
	InstanceBuffer();
	~InstanceBuffer();

	void upload(const void* data, std::size_t sizeInBytes);
	void bind();
	void unbind();

	unsigned int getVboID() const {
		return this->vboID;
	}
};
