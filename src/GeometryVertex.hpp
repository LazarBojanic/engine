#pragma once
#include "Util.hpp"


class GeometryVertex {
public:
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::vec4 boneIds;
	glm::vec4 weights;

	GeometryVertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv);
	GeometryVertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal);
	GeometryVertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal, glm::vec3 tangent,
	               glm::vec3 bitangent);
	GeometryVertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal, glm::vec3 tangent,
	               glm::vec3 bitangent, glm::vec4 boneIds, glm::vec4 weights);
	GeometryVertex();
	~GeometryVertex();
};
