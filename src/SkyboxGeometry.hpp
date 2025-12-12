#pragma once

#include "Geometry.hpp"

class SkyboxGeometry : public Geometry {
public:
    SkyboxGeometry(bool indexed) : Geometry(indexed) {
        if (isIndexed) {
            //Front
            /*00*/
            GeometryVertex vertexFLD1 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            /*01*/
            GeometryVertex vertexFRD1 = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            /*02*/
            GeometryVertex vertexFLU1 = GeometryVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            /*03*/
            GeometryVertex vertexFRU1 = GeometryVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

            //Right
            /*04*/
            GeometryVertex vertexFRD2 = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            /*05*/
            GeometryVertex vertexBRD1 = GeometryVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            /*06*/
            GeometryVertex vertexFRU2 = GeometryVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            /*07*/
            GeometryVertex vertexBRU1 = GeometryVertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            //Up
            /*08*/
            GeometryVertex vertexFLU2 = GeometryVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            /*09*/
            GeometryVertex vertexFRU3 = GeometryVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            /*10*/
            GeometryVertex vertexBLU1 = GeometryVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            /*11*/
            GeometryVertex vertexBRU2 = GeometryVertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            //Back
            /*12*/
            GeometryVertex vertexBRD2 = GeometryVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            /*13*/
            GeometryVertex vertexBLD1 = GeometryVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            /*14*/
            GeometryVertex vertexBRU3 = GeometryVertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            /*15*/
            GeometryVertex vertexBLU2 = GeometryVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

            //Left
            /*16*/
            GeometryVertex vertexBLD2 = GeometryVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            /*17*/
            GeometryVertex vertexFLD2 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            /*18*/
            GeometryVertex vertexBLU3 = GeometryVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            /*19*/
            GeometryVertex vertexFLU3 = GeometryVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

            //Down
            /*20*/
            GeometryVertex vertexBLD3 = GeometryVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            /*21*/
            GeometryVertex vertexBRD3 = GeometryVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            /*22*/
            GeometryVertex vertexFLD3 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            /*23*/
            GeometryVertex vertexFRD3 = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));


            //Front
            vertexList.push_back(vertexFLD1);
            vertexList.push_back(vertexFRD1);
            vertexList.push_back(vertexFLU1);
            vertexList.push_back(vertexFRU1);

            //Right
            vertexList.push_back(vertexFRD2);
            vertexList.push_back(vertexBRD1);
            vertexList.push_back(vertexFRU2);
            vertexList.push_back(vertexBRU1);

            //Up
            vertexList.push_back(vertexFLU2);
            vertexList.push_back(vertexFRU3);
            vertexList.push_back(vertexBLU1);
            vertexList.push_back(vertexBRU2);

            //Back
            vertexList.push_back(vertexBRD2);
            vertexList.push_back(vertexBLD1);
            vertexList.push_back(vertexBRU3);
            vertexList.push_back(vertexBLU2);
            //Left
            vertexList.push_back(vertexBLD2);
            vertexList.push_back(vertexFLD2);
            vertexList.push_back(vertexBLU3);
            vertexList.push_back(vertexFLU3);

            //Down
            vertexList.push_back(vertexBLD3);
            vertexList.push_back(vertexBRD3);
            vertexList.push_back(vertexFLD3);
            vertexList.push_back(vertexFRD3);
            //Front
            glm::uvec3 triangleFLD_FRD_FLU = glm::uvec3(0, 1, 2);
            glm::uvec3 triangleFLU_FRD_FRU = glm::uvec3(2, 1, 3);
            //Right
            glm::uvec3 triangleFRD_BRD_FRU = glm::uvec3(4, 5, 6);
            glm::uvec3 triangleFRU_BRD_BUR = glm::uvec3(6, 5, 7);
            //Up
            glm::uvec3 triangleFLU_FRU_BLU = glm::uvec3(8, 9, 10);
            glm::uvec3 triangleBLU_FRU_BRU = glm::uvec3(10, 9, 11);
            //Back
            glm::uvec3 triangleBRD_BLD_BRU = glm::uvec3(12, 13, 14);
            glm::uvec3 triangleBRU_BLD_BLU = glm::uvec3(14, 13, 15);
            //Left
            glm::uvec3 triangleBLD_FLD_BLU = glm::uvec3(16, 17, 18);
            glm::uvec3 triangleBLU_FLD_FLU = glm::uvec3(18, 17, 19);
            //Down
            glm::uvec3 triangleBLD_BRD_FLD = glm::uvec3(20, 21, 22);
            glm::uvec3 triangleFLD_BRD_FRD = glm::uvec3(22, 21, 23);

            triangleList.push_back(triangleFLD_FRD_FLU);
            triangleList.push_back(triangleFLU_FRD_FRU);

            triangleList.push_back(triangleFRD_BRD_FRU);
            triangleList.push_back(triangleFRU_BRD_BUR);

            triangleList.push_back(triangleFLU_FRU_BLU);
            triangleList.push_back(triangleBLU_FRU_BRU);

            triangleList.push_back(triangleBRD_BLD_BRU);
            triangleList.push_back(triangleBRU_BLD_BLU);

            triangleList.push_back(triangleBLD_FLD_BLU);
            triangleList.push_back(triangleBLU_FLD_FLU);

            triangleList.push_back(triangleBLD_BRD_FLD);
            triangleList.push_back(triangleFLD_BRD_FRD);
        }
        else {
            //Front
            GeometryVertex vertexFLD1 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            GeometryVertex vertexFRD1 = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            GeometryVertex vertexFLU1 = GeometryVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            GeometryVertex vertexFLU2 = GeometryVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            GeometryVertex vertexFRD2 = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            GeometryVertex vertexFRU1 = GeometryVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            //Right
            GeometryVertex vertexFRD3 = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            GeometryVertex vertexBRD1 = GeometryVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            GeometryVertex vertexFRU2 = GeometryVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            GeometryVertex vertexFRU3 = GeometryVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            GeometryVertex vertexBRD2 = GeometryVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            GeometryVertex vertexBRU1 = GeometryVertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            //Up
            GeometryVertex vertexFLU3 = GeometryVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            GeometryVertex vertexFRU4 = GeometryVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            GeometryVertex vertexBLU1 = GeometryVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            GeometryVertex vertexBLU2 = GeometryVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            GeometryVertex vertexFRU5 = GeometryVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            GeometryVertex vertexBRU2 = GeometryVertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            //Back
            GeometryVertex vertexBRD3 = GeometryVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            GeometryVertex vertexBLD1 = GeometryVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            GeometryVertex vertexBRU3 = GeometryVertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            GeometryVertex vertexBRU4 = GeometryVertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            GeometryVertex vertexBLD2 = GeometryVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            GeometryVertex vertexBLU3 = GeometryVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

            //Left
            GeometryVertex vertexBLD3 = GeometryVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            GeometryVertex vertexFLD2 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            GeometryVertex vertexBLU4 = GeometryVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            GeometryVertex vertexBLU5 = GeometryVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            GeometryVertex vertexFLD3 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            GeometryVertex vertexFLU4 = GeometryVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            //Down
            GeometryVertex vertexBLD4 = GeometryVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            GeometryVertex vertexBRD4 = GeometryVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            GeometryVertex vertexFLD4 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            GeometryVertex vertexFLD5 = GeometryVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            GeometryVertex vertexBRD5 = GeometryVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            GeometryVertex vertexFRD4 = GeometryVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));

            //Front
            vertexList.push_back(vertexFLD1);
            vertexList.push_back(vertexFRD1);
            vertexList.push_back(vertexFLU1);
            vertexList.push_back(vertexFLU2);
            vertexList.push_back(vertexFRD2);
            vertexList.push_back(vertexFRU1);

            //Right
            vertexList.push_back(vertexFRD3);
            vertexList.push_back(vertexBRD1);
            vertexList.push_back(vertexFRU2);
            vertexList.push_back(vertexFRU3);
            vertexList.push_back(vertexBRD2);
            vertexList.push_back(vertexBRU1);

            //Up
            vertexList.push_back(vertexFLU3);
            vertexList.push_back(vertexFRU4);
            vertexList.push_back(vertexBLU1);
            vertexList.push_back(vertexBLU2);
            vertexList.push_back(vertexFRU5);
            vertexList.push_back(vertexBRU2);

            //Back
            vertexList.push_back(vertexBRD3);
            vertexList.push_back(vertexBLD1);
            vertexList.push_back(vertexBRU3);
            vertexList.push_back(vertexBRU4);
            vertexList.push_back(vertexBLD2);
            vertexList.push_back(vertexBLU3);
            //Left
            vertexList.push_back(vertexBLD3);
            vertexList.push_back(vertexFLD2);
            vertexList.push_back(vertexBLU4);
            vertexList.push_back(vertexBLU5);
            vertexList.push_back(vertexFLD3);
            vertexList.push_back(vertexFLU4);

            //Down
            vertexList.push_back(vertexBLD4);
            vertexList.push_back(vertexBRD4);
            vertexList.push_back(vertexFLD4);
            vertexList.push_back(vertexFLD5);
            vertexList.push_back(vertexBRD5);
            vertexList.push_back(vertexFRD4);

        }
        finalize();
    }
};
