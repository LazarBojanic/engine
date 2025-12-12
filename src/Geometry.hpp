#pragma once

#include "Util.hpp"
#include "GeometryVertex.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

class Geometry {
protected:
    std::vector<GeometryVertex> vertexList;
    std::vector<float> rawVertexList;
    std::vector<glm::uvec3> triangleList;
    std::vector<unsigned int> rawIndexList;
    bool isIndexed;
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;

public:
    Geometry();
    Geometry(bool indexed);
    Geometry(bool indexed, std::vector<GeometryVertex> vertexList, std::vector<glm::uvec3> triangleList);
    Geometry(bool indexed, std::vector<GeometryVertex> vertexList, std::vector<unsigned int> indexList);
    ~Geometry();
    void calculateTangentsAndBitangents();
    void calculateRawData();
    void generateBuffers();
    void finalize();
    std::vector<GeometryVertex> getVertexList() {
        return this->vertexList;
    }

    std::vector<float> getRawVertexList() {
        return this->rawVertexList;
    }

    std::vector<glm::uvec3> getTriangleList() {
        return this->triangleList;
    }

    std::vector<unsigned int> getRawIndexList() {
        return this->rawIndexList;
    }

    bool getIsIndexed() {
        return this->isIndexed;
    }
    void setIsIndexed(bool isIndexed) {
        this->isIndexed = isIndexed;
    }

    GeometryVertex* getStructuredVertexData() {
        return this->vertexList.data();
    }

    unsigned int getStructuredVertexDataCount() {
        return this->vertexList.size();
    }

    unsigned int getStructuredVertexDataSize() {
        return this->getStructuredVertexDataCount() * sizeof(GeometryVertex);
    }

    float* getRawVertexData() {
        return this->rawVertexList.data();
    }

    unsigned int getRawVertexDataCount() {
        return this->rawVertexList.size();
    }

    unsigned int getRawVertexDataSize() {
        return this->getRawVertexDataCount() * sizeof(float);
    }

    unsigned int* getRawIndexData() {
        return this->rawIndexList.data();
    }

    unsigned int getRawIndexDataCount() {
        return this->rawIndexList.size();
    }

    unsigned int getRawIndexDataSize() {
        return this->getRawIndexDataCount() * sizeof(unsigned int);
    }

    std::shared_ptr<VertexArray> getVertexArray() {
        return this->vertexArray;
    }
    std::shared_ptr<VertexBuffer> getVertexBuffer() {
        return this->vertexBuffer;
    }
    std::shared_ptr<IndexBuffer> getIndexBuffer() {
        return this->indexBuffer;
    }
};
