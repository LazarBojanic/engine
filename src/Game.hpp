#pragma once

#include "Util.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "GameObjectManager.hpp"
#include "Renderer.hpp"
#include "TriangleGeometry.hpp"
#include "QuadGeometry.hpp"
#include "CubeGeometry.hpp"
#include "SkyboxGeometry.hpp"
#include "Window.hpp"
#include "Application.hpp"
#include "miniaudio/miniaudio.h"

class Game {
private:
    std::string workingDirectory;
    std::string ASSETS_PATH = "/home/lazar/dev/c-cpp/engine/assets/";
    static Game* instance;
    std::shared_ptr<ma_engine> soundEngine;
    bool* keys;
    int keysSize;
    float width;
    float height;
    float centerX;
    float centerY;
    std::shared_ptr<Camera> camera;
    float t;
    float orbitAngle = 0.0f;
    glm::vec3 orbitCenter = glm::vec3(50.0f, 50.0f, 50.0f);
public:
    Game();
    ~Game();
    static Game* getInstance();
    void initVariables();
    void initResources();
    void start();
    void processInput(float dt);
    void update(float dt);
    void render();
    void clear();
    void orbit(float dt);
    std::shared_ptr<Camera> getCamera() {
        return this->camera;
    }
    void initKeys();
    bool* getKeys() {
        return this->keys;
    }
    void generateCubeGrid(unsigned int gridSizeX, unsigned int gridSizeY, unsigned int gridSizeZ, float cubeSizeX, float cubeSizeY, float cubeSizeZ, float spacing);
};