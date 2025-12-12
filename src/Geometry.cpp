#include "Geometry.hpp"

Geometry::Geometry() {
    this->isIndexed = true;
    this->vertexList = std::vector<GeometryVertex>();
    this->triangleList = std::vector<glm::uvec3>();
    this->rawVertexList = std::vector<float>();
    this->rawIndexList = std::vector<unsigned int>();
}

Geometry::Geometry(bool indexed) {
    this->isIndexed = indexed;
    this->vertexList = std::vector<GeometryVertex>();
    this->triangleList = std::vector<glm::uvec3>();
    this->rawVertexList = std::vector<float>();
    this->rawIndexList = std::vector<unsigned int>();
}

Geometry::Geometry(bool indexed, std::vector<GeometryVertex> vertexList, std::vector<glm::uvec3> triangleList) {
    this->isIndexed = indexed;
    this->vertexList = vertexList;
    this->triangleList = triangleList;
    this->rawVertexList = std::vector<float>();
    this->rawIndexList = std::vector<unsigned int>();
    this->finalize();
}

Geometry::Geometry(bool indexed, std::vector<GeometryVertex> vertexList, std::vector<unsigned int> indexList) {
    this->isIndexed = indexed;
    this->vertexList = vertexList;
    this->triangleList = std::vector<glm::uvec3>();
    this->rawVertexList = std::vector<float>();
    this->rawIndexList = indexList;
    this->finalize();
}

Geometry::~Geometry() {
}

void Geometry::calculateTangentsAndBitangents() {
// Reset tangents and bitangents to zero
    for (auto& vertex : vertexList) {
        vertex.tangent = glm::vec3(0.0f);
        vertex.bitangent = glm::vec3(0.0f);
    }

    // Use triangle list if indexed
    if (isIndexed && !triangleList.empty()) {
        for (const auto& tri : triangleList) {
            GeometryVertex& v0 = vertexList[tri.x];
            GeometryVertex& v1 = vertexList[tri.y];
            GeometryVertex& v2 = vertexList[tri.z];

            // Positions and UVs
            glm::vec3 pos0 = v0.position;
            glm::vec3 pos1 = v1.position;
            glm::vec3 pos2 = v2.position;

            glm::vec2 uv0 = v0.uv;
            glm::vec2 uv1 = v1.uv;
            glm::vec2 uv2 = v2.uv;

            // Edges of the triangle (position delta)
            glm::vec3 deltaPos1 = pos1 - pos0;
            glm::vec3 deltaPos2 = pos2 - pos0;

            // UV delta
            glm::vec2 deltaUV1 = uv1 - uv0;
            glm::vec2 deltaUV2 = uv2 - uv0;

            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            // Accumulate per-vertex
            v0.tangent += tangent;
            v1.tangent += tangent;
            v2.tangent += tangent;

            v0.bitangent += bitangent;
            v1.bitangent += bitangent;
            v2.bitangent += bitangent;
        }
    }
    // Fallback for non-indexed geometry (triangle soup)
    else {
        for (size_t i = 0; i + 2 < vertexList.size(); i += 3) {
            GeometryVertex& v0 = vertexList[i + 0];
            GeometryVertex& v1 = vertexList[i + 1];
            GeometryVertex& v2 = vertexList[i + 2];

            glm::vec3 pos0 = v0.position;
            glm::vec3 pos1 = v1.position;
            glm::vec3 pos2 = v2.position;

            glm::vec2 uv0 = v0.uv;
            glm::vec2 uv1 = v1.uv;
            glm::vec2 uv2 = v2.uv;

            glm::vec3 deltaPos1 = pos1 - pos0;
            glm::vec3 deltaPos2 = pos2 - pos0;

            glm::vec2 deltaUV1 = uv1 - uv0;
            glm::vec2 deltaUV2 = uv2 - uv0;

            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            v0.tangent += tangent;
            v1.tangent += tangent;
            v2.tangent += tangent;

            v0.bitangent += bitangent;
            v1.bitangent += bitangent;
            v2.bitangent += bitangent;
        }
    }

    // Normalize results
    for (auto& vertex : vertexList) {
        vertex.tangent = glm::normalize(vertex.tangent);
        vertex.bitangent = glm::normalize(vertex.bitangent);
    }
}

void Geometry::calculateRawData() {
    for (auto vertex : this->vertexList) {
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


    if (this->isIndexed) {
        if (!this->triangleList.empty()) {
            for (auto triangle : this->triangleList) {
                this->rawIndexList.push_back(triangle.x);
                this->rawIndexList.push_back(triangle.y);
                this->rawIndexList.push_back(triangle.z);
            }
        }
        // Else: rawIndexList already filled from constructor
    }
}

void Geometry::generateBuffers() {
    if (this->getStructuredVertexDataCount() <= 0) return;
    this->vertexArray = std::make_shared<VertexArray>();
    this->vertexArray->bind();
    this->vertexBuffer = std::make_shared<VertexBuffer>();
    this->vertexBuffer->uploadData(this->getStructuredVertexData(), this->getStructuredVertexDataCount(), this->getStructuredVertexDataSize());
    this->vertexBuffer->bind();
    if (this->isIndexed) {
        this->indexBuffer = std::make_shared<IndexBuffer>();
        this->indexBuffer->uploadData(this->getRawIndexData(), this->getRawIndexDataCount(), this->getRawIndexDataSize());
        this->indexBuffer->bind();
    }
    this->vertexArray->unbind();
}

void Geometry::finalize() {
    this->calculateTangentsAndBitangents();
    this->calculateRawData();
    this->generateBuffers();
}
