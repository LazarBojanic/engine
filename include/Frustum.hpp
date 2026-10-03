#pragma once

#include "Util.hpp"

class Frustum {
private:
	glm::vec4 planes[6];

public:
	Frustum() = default;

	void update(const glm::mat4& viewProjection);
	bool testSphere(const glm::vec3& center, float radius) const;
	bool testAABB(const glm::vec3& min, const glm::vec3& max) const;
};
