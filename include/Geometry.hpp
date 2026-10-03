#pragma once

#include "Util.hpp"
#include "GeometryVertex.hpp"
#include "IndexBuffer.hpp"
#include "InstanceBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

class Geometry {
protected:
    std::vector<GeometryVertex> vertexList;
    std::vector<float> rawVertexList;
    std::vector<glm::uvec3> triangleList;
    std::vector<unsigned int> rawIndexList;
    bool isIndexed;
    glm::vec3 localAABBMin{ 0.0f };
    glm::vec3 localAABBMax{ 0.0f };
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::shared_ptr<InstanceBuffer> instanceBuffer;

public:
    Geometry();
    Geometry(bool indexed);
    Geometry(bool indexed, std::vector<GeometryVertex> vertexList, std::vector<glm::uvec3> triangleList);
    Geometry(bool indexed, std::vector<GeometryVertex> vertexList, std::vector<unsigned int> indexList);
    ~Geometry();

    void calculateTangentsAndBitangents();
    void calculateRawData();
    void calculateLocalAABB();
    void generateBuffers();
    void finalize();

    const std::vector<GeometryVertex>& getVertexList() const {
        return this->vertexList;
    }

    const std::vector<float>& getRawVertexList() const {
        return this->rawVertexList;
    }

    const std::vector<glm::uvec3>& getTriangleList() const {
        return this->triangleList;
    }

    const std::vector<unsigned int>& getRawIndexList() const {
        return this->rawIndexList;
    }

    bool getIsIndexed() const {
        return this->isIndexed;
    }

    void setIsIndexed(bool isIndexed) {
        this->isIndexed = isIndexed;
    }

    GeometryVertex* getStructuredVertexData() {
        return this->vertexList.data();
    }

    unsigned int getStructuredVertexDataCount() const {
        return static_cast<unsigned int>(this->vertexList.size());
    }

    unsigned int getStructuredVertexDataSize() const {
        return this->getStructuredVertexDataCount() * static_cast<unsigned int>(sizeof(GeometryVertex));
    }

    float* getRawVertexData() {
        return this->rawVertexList.data();
    }

    unsigned int getRawVertexDataCount() const {
        return static_cast<unsigned int>(this->rawVertexList.size());
    }

    unsigned int getRawVertexDataSize() const {
        return this->getRawVertexDataCount() * static_cast<unsigned int>(sizeof(float));
    }

    unsigned int* getRawIndexData() {
        return this->rawIndexList.data();
    }

    unsigned int getRawIndexDataCount() const {
        return static_cast<unsigned int>(this->rawIndexList.size());
    }

    unsigned int getRawIndexDataSize() const {
        return this->getRawIndexDataCount() * static_cast<unsigned int>(sizeof(unsigned int));
    }

    const glm::vec3& getLocalAABBMin() const {
        return this->localAABBMin;
    }

    const glm::vec3& getLocalAABBMax() const {
        return this->localAABBMax;
    }

    const std::shared_ptr<VertexArray>& getVertexArray() const {
        return this->vertexArray;
    }

    const std::shared_ptr<VertexBuffer>& getVertexBuffer() const {
        return this->vertexBuffer;
    }

    const std::shared_ptr<IndexBuffer>& getIndexBuffer() const {
        return this->indexBuffer;
    }

    const std::shared_ptr<InstanceBuffer>& getInstanceBuffer() const {
        return this->instanceBuffer;
    }
};
