#pragma once
#include "Util.hpp"
#include "WindowConfig.hpp"

class Window {
private:
    GLFWwindow* glfwWindow;
    int posX;
    int posY;
    int width;
    int height;
    std::string title;
    bool fullscreen;
    bool vsync;
    bool resizable;
    void initGlfw();
    void initGlad();
    void initGlfwWindow();

public:
    Window();
    Window(int width, int height, const std::string& title);
    Window(WindowConfig* windowConfig);
    static void error_callback(int error, const char* description);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                         const GLchar* message, const void* userParam);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    ~Window();

    GLFWwindow* getGlfwWindow() {
        return this->glfwWindow;
    }

    int getPosX() {
        return this->posX;
    }

    int getPosY() {
        return this->posY;
    }

    int getWidth() {
        return this->width;
    }

    int getHeight() {
        return this->height;
    }

    std::string getTitle() {
        return this->title;
    }

    bool getFullscreen() {
        return this->fullscreen;
    }

    bool getVsync() {
        return this->vsync;
    }

    bool getResizable() {
        return resizable;
    }

    void setPosX(int posX) {
        this->posX = posX;
    }

    void setPosY(int posY) {
        this->posY = posY;
    }

    void setWidth(int width) {
        this->width = width;
    }

    void setHeight(int height) {
        this->height = height;
    }

    void setTitle(const std::string& title) {
        this->title = title;
        glfwSetWindowTitle(this->glfwWindow, this->title.c_str());
    }

    void setFullscreen(int fullscreen) {
        this->fullscreen = fullscreen;
    }

    void setVsync(int vsync) {
        this->vsync = vsync;
    }

    void setResizable(int resizable) {
        this->resizable = resizable;
    }
};
