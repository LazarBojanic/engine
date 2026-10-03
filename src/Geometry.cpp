#include "Geometry.hpp"

#include <cstddef>
#include <limits>

Geometry::Geometry() {
    this->isIndexed = true;
}

Geometry::Geometry(bool indexed) {
    this->isIndexed = indexed;
}

Geometry::Geometry(bool indexed, std::vector<GeometryVertex> vertexList, std::vector<glm::uvec3> triangleList) {
    this->isIndexed = indexed;
    this->vertexList = std::move(vertexList);
    this->triangleList = std::move(triangleList);
    this->finalize();
}

Geometry::Geometry(bool indexed, std::vector<GeometryVertex> vertexList, std::vector<unsigned int> indexList) {
    this->isIndexed = indexed;
    this->vertexList = std::move(vertexList);
    this->rawIndexList = std::move(indexList);
    this->finalize();
}

Geometry::~Geometry() {
}

void Geometry::calculateTangentsAndBitangents() {
    for (auto& vertex : this->vertexList) {
        vertex.tangent = glm::vec3(0.0f);
        vertex.bitangent = glm::vec3(0.0f);
    }

    if (this->isIndexed && !this->triangleList.empty()) {
        for (const auto& triangle : this->triangleList) {
            GeometryVertex& v0 = this->vertexList[triangle.x];
            GeometryVertex& v1 = this->vertexList[triangle.y];
            GeometryVertex& v2 = this->vertexList[triangle.z];

            const glm::vec3 deltaPos1 = v1.position - v0.position;
            const glm::vec3 deltaPos2 = v2.position - v0.position;
            const glm::vec2 deltaUV1 = v1.uv - v0.uv;
            const glm::vec2 deltaUV2 = v2.uv - v0.uv;

            const float determinant = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
            const float r = determinant != 0.0f ? 1.0f / determinant : 0.0f;
            const glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            const glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            v0.tangent += tangent;
            v1.tangent += tangent;
            v2.tangent += tangent;

            v0.bitangent += bitangent;
            v1.bitangent += bitangent;
            v2.bitangent += bitangent;
        }
    }
    else {
        for (std::size_t i = 0; i + 2 < this->vertexList.size(); i += 3) {
            GeometryVertex& v0 = this->vertexList[i + 0];
            GeometryVertex& v1 = this->vertexList[i + 1];
            GeometryVertex& v2 = this->vertexList[i + 2];

            const glm::vec3 deltaPos1 = v1.position - v0.position;
            const glm::vec3 deltaPos2 = v2.position - v0.position;
            const glm::vec2 deltaUV1 = v1.uv - v0.uv;
            const glm::vec2 deltaUV2 = v2.uv - v0.uv;

            const float determinant = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
            const float r = determinant != 0.0f ? 1.0f / determinant : 0.0f;
            const glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            const glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            v0.tangent += tangent;
            v1.tangent += tangent;
            v2.tangent += tangent;

            v0.bitangent += bitangent;
            v1.bitangent += bitangent;
            v2.bitangent += bitangent;
        }
    }

    for (auto& vertex : this->vertexList) {
        const float tangentLength = glm::length(vertex.tangent);
        if (tangentLength > 0.0f) {
            vertex.tangent /= tangentLength;
        }
        const float bitangentLength = glm::length(vertex.bitangent);
        if (bitangentLength > 0.0f) {
            vertex.bitangent /= bitangentLength;
        }
    }
}

void Geometry::calculateRawData() {
    this->rawVertexList.clear();
    this->rawVertexList.reserve(this->vertexList.size() * 25);

    for (const auto& vertex : this->vertexList) {
        this->rawVertexList.push_back(vertex.position.x);
        this->rawVertexList.push_back(vertex.position.y);
        this->rawVertexList.push_back(vertex.position.z);

        this->rawVertexList.push_back(vertex.color.x);
        this->rawVertexList.push_back(vertex.color.y);
        this->rawVertexList.push_back(vertex.color.z);

        this->rawVertexList.push_back(vertex.uv.x);
        this->rawVertexList.push_back(vertex.uv.y);

        this->rawVertexList.push_back(vertex.normal.x);
        this->rawVertexList.push_back(vertex.normal.y);
        this->rawVertexList.push_back(vertex.normal.z);

        this->rawVertexList.push_back(vertex.tangent.x);
        this->rawVertexList.push_back(vertex.tangent.y);
        this->rawVertexList.push_back(vertex.tangent.z);

        this->rawVertexList.push_back(vertex.bitangent.x);
        this->rawVertexList.push_back(vertex.bitangent.y);
        this->rawVertexList.push_back(vertex.bitangent.z);

        this->rawVertexList.push_back(vertex.boneIds.x);
        this->rawVertexList.push_back(vertex.boneIds.y);
        this->rawVertexList.push_back(vertex.boneIds.z);
        this->rawVertexList.push_back(vertex.boneIds.w);

        this->rawVertexList.push_back(vertex.weights.x);
        this->rawVertexList.push_back(vertex.weights.y);
        this->rawVertexList.push_back(vertex.weights.z);
        this->rawVertexList.push_back(vertex.weights.w);
    }

    if (this->isIndexed && !this->triangleList.empty()) {
        this->rawIndexList.clear();
        this->rawIndexList.reserve(this->triangleList.size() * 3);
        for (const auto& triangle : this->triangleList) {
            this->rawIndexList.push_back(triangle.x);
            this->rawIndexList.push_back(triangle.y);
            this->rawIndexList.push_back(triangle.z);
        }
    }
}

void Geometry::calculateLocalAABB() {
    if (this->vertexList.empty()) {
        this->localAABBMin = glm::vec3(0.0f);
        this->localAABBMax = glm::vec3(0.0f);
        return;
    }

    constexpr float maxFloat = std::numeric_limits<float>::max();
    glm::vec3 min(maxFloat);
    glm::vec3 max(-maxFloat);
    for (const auto& vertex : this->vertexList) {
        min = glm::min(min, vertex.position);
        max = glm::max(max, vertex.position);
    }
    this->localAABBMin = min;
    this->localAABBMax = max;
}

void Geometry::generateBuffers() {
    if (this->getStructuredVertexDataCount() == 0) {
        return;
    }

    this->vertexArray = std::make_shared<VertexArray>();
    this->vertexArray->bind();

    this->vertexBuffer = std::make_shared<VertexBuffer>();
    this->vertexBuffer->uploadData(this->getStructuredVertexData(), this->getStructuredVertexDataCount(), this->getStructuredVertexDataSize());

    if (this->isIndexed) {
        this->indexBuffer = std::make_shared<IndexBuffer>();
        this->indexBuffer->uploadData(this->getRawIndexData(), this->getRawIndexDataCount(), this->getRawIndexDataSize());
    }

    this->instanceBuffer = std::make_shared<InstanceBuffer>();
    this->instanceBuffer->bind();
    const InstanceData identity;
    this->instanceBuffer->upload(&identity, sizeof(InstanceData));

    for (GLuint i = 0; i < 4; i++) {
        const GLuint location = Util::LAYOUT_LOCATION_INSTANCE_MODEL + i;
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
            reinterpret_cast<const void*>(offsetof(InstanceData, model) + sizeof(glm::vec4) * i));
        glVertexAttribDivisor(location, 1);
    }
    for (GLuint i = 0; i < 4; i++) {
        const GLuint location = Util::LAYOUT_LOCATION_INSTANCE_INVERSE + i;
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData),
            reinterpret_cast<const void*>(offsetof(InstanceData, inverseModel) + sizeof(glm::vec4) * i));
        glVertexAttribDivisor(location, 1);
    }

    this->vertexArray->unbind();
}

void Geometry::finalize() {
    this->calculateTangentsAndBitangents();
    this->calculateRawData();
    this->calculateLocalAABB();
    this->generateBuffers();
}
