#include "Frustum.hpp"

void Frustum::update(const glm::mat4& viewProjection) {
	const glm::vec4 row0(viewProjection[0][0], viewProjection[1][0], viewProjection[2][0], viewProjection[3][0]);
	const glm::vec4 row1(viewProjection[0][1], viewProjection[1][1], viewProjection[2][1], viewProjection[3][1]);
	const glm::vec4 row2(viewProjection[0][2], viewProjection[1][2], viewProjection[2][2], viewProjection[3][2]);
	const glm::vec4 row3(viewProjection[0][3], viewProjection[1][3], viewProjection[2][3], viewProjection[3][3]);

	this->planes[0] = row3 + row0; // left
	this->planes[1] = row3 - row0; // right
	this->planes[2] = row3 + row1; // bottom
	this->planes[3] = row3 - row1; // top
	this->planes[4] = row3 + row2; // near
	this->planes[5] = row3 - row2; // far

	for (glm::vec4& plane : this->planes) {
		const float length = glm::length(glm::vec3(plane));
		if (length > 0.0f) {
			plane /= length;
		}
	}
}

bool Frustum::testSphere(const glm::vec3& center, float radius) const {
	for (const glm::vec4& plane : this->planes) {
		if (glm::dot(glm::vec3(plane), center) + plane.w < -radius) {
			return false;
		}
	}
	return true;
}

bool Frustum::testAABB(const glm::vec3& min, const glm::vec3& max) const {
	for (const glm::vec4& plane : this->planes) {
		const glm::vec3 positive(
			plane.x >= 0.0f ? max.x : min.x,
			plane.y >= 0.0f ? max.y : min.y,
			plane.z >= 0.0f ? max.z : min.z);
		if (glm::dot(glm::vec3(plane), positive) + plane.w < 0.0f) {
			return false;
		}
	}
	return true;
}
