#pragma once

#include "Geometry.hpp"

class TriangleGeometry : public Geometry {
public:
    TriangleGeometry(bool indexed) : Geometry(indexed){
        GeometryVertex vertexLD = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f));
        GeometryVertex vertexRD = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.0f),    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f));
        GeometryVertex vertexT = GeometryVertex(glm::vec3(0.0f,  0.5f, 0.0f),    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f));
        vertexList.push_back(vertexLD);
        vertexList.push_back(vertexRD);
        vertexList.push_back(vertexT);
        glm::uvec3 triangleLD_RD_T = glm::uvec3(0, 1, 2);
        triangleList.push_back(triangleLD_RD_T);
        finalize();
    }
};