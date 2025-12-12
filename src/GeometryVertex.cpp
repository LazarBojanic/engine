#include "GeometryVertex.hpp"

GeometryVertex::GeometryVertex() {
    this->position = glm::vec3(0.0f);
    this->color = glm::vec4(1.0f);
    this->uv = glm::vec2(0.0f);
    this->normal = glm::vec3(1.0f);
    this->tangent = glm::vec3(0.0f);
    this->bitangent = glm::vec3(0.0f);
    this->boneIds = glm::vec4(0.0f);
    this->weights = glm::vec4(0.0f);
}

GeometryVertex::GeometryVertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv) {
    this->position = position;
    this->color = color;
    this->uv = uv;
    this->normal = glm::vec3(0.0f);
    this->tangent = glm::vec3(0.0f);
    this->bitangent = glm::vec3(0.0f);
    this->boneIds = glm::vec4(0.0f);
    this->weights = glm::vec4(0.0f);
}

GeometryVertex::GeometryVertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal) {
    this->position = position;
    this->color = color;
    this->uv = uv;
    this->normal = normal;
    this->tangent = glm::vec3(0.0f);
    this->bitangent = glm::vec3(0.0f);
    this->boneIds = glm::vec4(0.0f);
    this->weights = glm::vec4(0.0f);
}

GeometryVertex::GeometryVertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal, glm::vec3 tangent,
                               glm::vec3 bitangent) {
    this->position = position;
    this->color = color;
    this->uv = uv;
    this->normal = normal;
    this->tangent = tangent;
    this->bitangent = bitangent;
    this->boneIds = glm::vec4(0.0f);
    this->weights = glm::vec4(0.0f);
}

GeometryVertex::GeometryVertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal, glm::vec3 tangent,
                               glm::vec3 bitangent, glm::vec4 boneIds, glm::vec4 weights) {
    this->position = position;
    this->color = color;
    this->uv = uv;
    this->normal = normal;
    this->tangent = tangent;
    this->bitangent = bitangent;
    this->boneIds = boneIds;
    this->weights = weights;
}

GeometryVertex::~GeometryVertex() {
}



