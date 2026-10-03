#pragma once

#include "Util.hpp"
#include <cmath>

class Transform {
private:
	glm::vec3 position{ 0.0f };
	glm::vec3 rotation{ 0.0f };
	glm::vec3 scale{ 1.0f };
	glm::vec3 size{ 1.0f };
	glm::vec3 localMin{ -0.5f };
	glm::vec3 localMax{ 0.5f };

	mutable bool dirty{ true };
	mutable glm::mat4 modelMatrix{ 1.0f };
	mutable glm::mat4 inverseModelMatrix{ 1.0f };
	mutable glm::vec3 worldAABBMin{ 0.0f };
	mutable glm::vec3 worldAABBMax{ 0.0f };
	mutable glm::vec3 worldCenter{ 0.0f };
	mutable float worldRadius{ 0.0f };

	void updateCaches() const {
		this->modelMatrix = glm::mat4(1.0f);
		this->modelMatrix = glm::translate(this->modelMatrix, this->position);
		this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->modelMatrix = glm::scale(this->modelMatrix, this->getScaledSize());
		this->inverseModelMatrix = glm::transpose(glm::inverse(this->modelMatrix));

		const glm::vec3 localCenter = (this->localMin + this->localMax) * 0.5f;
		const glm::vec3 localExtent = (this->localMax - this->localMin) * 0.5f;
		this->worldCenter = glm::vec3(this->modelMatrix * glm::vec4(localCenter, 1.0f));

		const glm::mat3 basis(this->modelMatrix);
		const glm::vec3 worldExtent(
			std::abs(basis[0][0]) * localExtent.x + std::abs(basis[1][0]) * localExtent.y + std::abs(basis[2][0]) * localExtent.z,
			std::abs(basis[0][1]) * localExtent.x + std::abs(basis[1][1]) * localExtent.y + std::abs(basis[2][1]) * localExtent.z,
			std::abs(basis[0][2]) * localExtent.x + std::abs(basis[1][2]) * localExtent.y + std::abs(basis[2][2]) * localExtent.z);

		this->worldAABBMin = this->worldCenter - worldExtent;
		this->worldAABBMax = this->worldCenter + worldExtent;
		this->worldRadius = glm::length(worldExtent);
		this->dirty = false;
	}

public:
	Transform() = default;

	void setLocalBounds(const glm::vec3& min, const glm::vec3& max) {
		this->localMin = min;
		this->localMax = max;
		this->dirty = true;
	}

	void setPosition(const glm::vec3& position) {
		this->position = position;
		this->dirty = true;
	}

	void setPositionX(float x) {
		this->position.x = x;
		this->dirty = true;
	}

	void setPositionY(float y) {
		this->position.y = y;
		this->dirty = true;
	}

	void setPositionZ(float z) {
		this->position.z = z;
		this->dirty = true;
	}

	void setRotation(const glm::vec3& rotation) {
		this->rotation = rotation;
		this->dirty = true;
	}

	void setRotationX(float x) {
		this->rotation.x = x;
		this->dirty = true;
	}

	void setRotationY(float y) {
		this->rotation.y = y;
		this->dirty = true;
	}

	void setRotationZ(float z) {
		this->rotation.z = z;
		this->dirty = true;
	}

	void setScale(const glm::vec3& scale) {
		this->scale = scale;
		this->dirty = true;
	}

	void setScaleX(float x) {
		this->scale.x = x;
		this->dirty = true;
	}

	void setScaleY(float y) {
		this->scale.y = y;
		this->dirty = true;
	}

	void setScaleZ(float z) {
		this->scale.z = z;
		this->dirty = true;
	}

	void setSize(const glm::vec3& size) {
		this->size = size;
		this->dirty = true;
	}

	void setSizeX(float x) {
		this->size.x = x;
		this->dirty = true;
	}

	void setSizeY(float y) {
		this->size.y = y;
		this->dirty = true;
	}

	void setSizeZ(float z) {
		this->size.z = z;
		this->dirty = true;
	}

	const glm::vec3& getPosition() const { return this->position; }
	float getPositionX() const { return this->position.x; }
	float getPositionY() const { return this->position.y; }
	float getPositionZ() const { return this->position.z; }

	const glm::vec3& getRotation() const { return this->rotation; }
	float getRotationX() const { return this->rotation.x; }
	float getRotationY() const { return this->rotation.y; }
	float getRotationZ() const { return this->rotation.z; }

	const glm::vec3& getScale() const { return this->scale; }
	float getScaleX() const { return this->scale.x; }
	float getScaleY() const { return this->scale.y; }
	float getScaleZ() const { return this->scale.z; }

	const glm::vec3& getSize() const { return this->size; }
	float getSizeX() const { return this->size.x; }
	float getSizeY() const { return this->size.y; }
	float getSizeZ() const { return this->size.z; }

	glm::vec3 getScaledSize() const { return this->size * this->scale; }
	float getScaledSizeX() const { return this->size.x * this->scale.x; }
	float getScaledSizeY() const { return this->size.y * this->scale.y; }
	float getScaledSizeZ() const { return this->size.z * this->scale.z; }

	const glm::mat4& getModelMatrix() const {
		if (this->dirty) {
			this->updateCaches();
		}
		return this->modelMatrix;
	}

	const glm::mat4& getInverseModelMatrix() const {
		if (this->dirty) {
			this->updateCaches();
		}
		return this->inverseModelMatrix;
	}

	const glm::vec3& getWorldAABBMin() const {
		if (this->dirty) {
			this->updateCaches();
		}
		return this->worldAABBMin;
	}

	const glm::vec3& getWorldAABBMax() const {
		if (this->dirty) {
			this->updateCaches();
		}
		return this->worldAABBMax;
	}

	const glm::vec3& getWorldCenter() const {
		if (this->dirty) {
			this->updateCaches();
		}
		return this->worldCenter;
	}

	float getWorldRadius() const {
		if (this->dirty) {
			this->updateCaches();
		}
		return this->worldRadius;
	}
};
