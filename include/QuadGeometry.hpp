#pragma once

#include "Geometry.hpp"

class Quad : public Geometry {
public:
    Quad(bool indexed) : Geometry(indexed){
        if (isIndexed) {
            GeometryVertex vertexLD = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            GeometryVertex vertexRD = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.0f),    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            GeometryVertex vertexRU = GeometryVertex(glm::vec3(0.5f,  0.5f, 0.0f),    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            GeometryVertex vertexLU = GeometryVertex(glm::vec3(-0.5f, 0.5f, 0.0f),   glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            vertexList.push_back(vertexLD);
            vertexList.push_back(vertexRD);
            vertexList.push_back(vertexRU);
            vertexList.push_back(vertexLU);
            glm::uvec3 triangleLD_RD_RU = glm::uvec3(0, 1, 2);
            glm::uvec3 triangleRU_LU_LD = glm::uvec3(2, 3, 0);
            triangleList.push_back(triangleLD_RD_RU);
            triangleList.push_back(triangleRU_LU_LD);
        }
        else {
            GeometryVertex vertexLD1 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            GeometryVertex vertexRD1 = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.0f),    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            GeometryVertex vertexRU1 = GeometryVertex(glm::vec3(0.5f,  0.5f, 0.0f),    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            GeometryVertex vertexRU2 = GeometryVertex(glm::vec3(0.5f,  0.5f, 0.0f),    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            GeometryVertex vertexLU1 = GeometryVertex(glm::vec3(-0.5f,  0.5f, 0.0f),   glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            GeometryVertex vertexLD2 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f));
            vertexList.push_back(vertexLD1);
            vertexList.push_back(vertexRD1);
            vertexList.push_back(vertexRU1);
            vertexList.push_back(vertexRU2);
            vertexList.push_back(vertexLU1);
            vertexList.push_back(vertexLD2);
        }
        finalize();
    }
};