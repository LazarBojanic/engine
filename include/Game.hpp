#pragma once

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

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
#include <array>
#include <filesystem>

class Game {
private:
    std::string workingDirectory;
    static Game* instance;
    std::shared_ptr<ma_engine> soundEngine;
    std::array<bool, 1024> keys{};
    float width;
    float height;
    float centerX;
    float centerY;
    std::shared_ptr<Camera> camera;
    float t = 0.0f;
    float orbitAngle = 0.0f;
    glm::vec3 orbitCenter = glm::vec3(50.0f, 50.0f, 50.0f);
    glm::vec3 backpackInitialPosition = glm::vec3(30.0f, 30.0f, 30.0f);
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
    const std::shared_ptr<Camera>& getCamera() const {
        return this->camera;
    }
    void initKeys();
    bool* getKeys() {
        return this->keys.data();
    }
    void generateCubeGrid(unsigned int gridSizeX, unsigned int gridSizeY, unsigned int gridSizeZ, float cubeSizeX, float cubeSizeY, float cubeSizeZ, float spacing);
};
