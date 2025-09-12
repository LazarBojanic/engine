#include "Application.hpp"

Application* Application::instance;

Application::Application() {
    this->window = new Window();
}

Application::Application(WindowConfig* windowConfig) {
    this->window = new Window(windowConfig);
}

Application::Application(int width, int height, const std::string& title) {
    this->window = new Window(width, height, title);
}

Application* Application::getInstance() {
    if (!instance) {
        instance = new Application();
    }
    return instance;
}

Application* Application::getInstance(WindowConfig* windowConfig) {
    if (!instance) {
        instance = new Application(windowConfig);
    }
    return instance;
}

Application* Application::getInstance(int width, int height, const std::string& title) {
    if (!instance) {
        std::cout << "Creating app" << std::endl;
        instance = new Application(width, height, title);
    }
    return instance;
}

Application::~Application() {
    delete this->window;
}


void Application::run() {
    std::cout << "Running Application" << std::endl;
    Game::getInstance()->start();
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    int frameCount = 0;
    float fpsTimer = 0.0f;

    while (!glfwWindowShouldClose(window->getGlfwWindow())) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        frameCount++;
        fpsTimer += deltaTime;

        if (fpsTimer >= 1.0f) {
            float fps = frameCount / fpsTimer;
            fpsTimer = 0.0f;
            frameCount = 0;

            std::string newTitle = "FPS: " + std::to_string(fps);

            window->setTitle(newTitle);
        }

        Game::getInstance()->processInput(deltaTime);

        Game::getInstance()->update(deltaTime);

        Game::getInstance()->render();
    }
    ResourceManager::getInstance()->clear(false);
    GameObjectManager::getInstance()->clear(false);
    Game::getInstance()->clear();
}
