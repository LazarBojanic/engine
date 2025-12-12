
#include "Window.hpp"

#include "Application.hpp"
#include "Game.hpp"

void Window::initGlfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, this->resizable);
}

void Window::initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void Window::initGlfwWindow() {
    std::cout << "Initializing GLFW window..." << std::endl;
    this->glfwWindow = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
    if (this->glfwWindow == NULL) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->glfwWindow);
    //glfwSetWindowUserPointer(this->glfwWindow, this);
    this->initGlad();
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallback, 0);
    glfwSetKeyCallback(this->glfwWindow, key_callback);
    glfwSetFramebufferSizeCallback(this->glfwWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(this->glfwWindow, mouse_callback);
    glfwSetScrollCallback(this->glfwWindow, scroll_callback);
    glfwSwapInterval(this->vsync);
    glfwSetWindowPos(this->glfwWindow, 600, 300);
    glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::Window() {
    this->posX = 600;
    this->posY = 300;
    this->width = 800;
    this->height = 600;
    this->title = "3D Template";
    this->fullscreen = false;
    this->vsync = false;
    this->resizable = true;
    this->initGlfw();
    this->initGlfwWindow();
}

Window::Window(int width, int height, const std::string& title) {
    this->posX = 600;
    this->posY = 300;
    this->width = width;
    this->height = height;
    this->title = title;
    this->fullscreen = false;
    this->vsync = false;
    this->resizable = true;
    this->initGlfw();
    this->initGlfwWindow();
}

Window::Window(WindowConfig* windowConfig) {
    this->posX = windowConfig->posX;
    this->posY = windowConfig->posY;
    this->width = windowConfig->width;
    this->height = windowConfig->height;
    this->title = windowConfig->title;
    this->fullscreen = windowConfig->fullscreen;
    this->vsync = windowConfig->vsync;
    this->resizable = windowConfig->resizable;
    this->initGlfw();
    this->initGlfwWindow();
}



void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Application::getInstance()->getWindow()->setWidth(width);
    Application::getInstance()->getWindow()->setHeight(height);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            Game::getInstance()->getKeys()[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            Game::getInstance()->getKeys()[key] = false;
        }
    }
}

void Window::debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                           const GLchar* message, const void* userParam) {
    std::string messageString = std::string(message);
    if (messageString.find("will use VIDEO memory as the source for buffer object operations") == std::string::npos) {
        std::cout << "GL CALLBACK-> Type: " << Util::getDebugMeaning(type) << ", Severity: " <<
        Util::getDebugMeaning(severity) << ", Message: " << message << std::endl;
    }
}

void Window::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (Game::getInstance()->getCamera()->getFirstMouse()) {
        Game::getInstance()->getCamera()->setLastX(xpos);
        Game::getInstance()->getCamera()->setLastY(ypos);
        Game::getInstance()->getCamera()->setFirstMouse(false);
    }

    float xoffset = xpos - Game::getInstance()->getCamera()->getLastX();
    float yoffset = Game::getInstance()->getCamera()->getLastY() - ypos;

    Game::getInstance()->getCamera()->setLastX(xpos);
    Game::getInstance()->getCamera()->setLastY(ypos);

    Game::getInstance()->getCamera()->processMouseMovement(xoffset, yoffset, true);
}


void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Game::getInstance()->getCamera()->processMouseScroll(static_cast<float>(yoffset));
}

Window::~Window() {
    glfwDestroyWindow(this->glfwWindow);
}

