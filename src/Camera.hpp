#pragma once

#include "Util.hpp"
#include "Window.hpp"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
private:
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float screenWidth;
    float screenHeight;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
    float lastX;
    float lastY;
    bool firstMouse;
public:
    Camera(glm::vec3 position, float width, float height, float nearPlane, float farPlane);
    Camera(float positionX, float positionY, float positionZ, float width, float height, float nearPlane, float farPlane);
    ~Camera();
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
    void updateView();
    void updateProjection();
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseScroll(float yoffset);
    glm::mat4 getView(){
        return this->view;
    }
    glm::mat4 getProjection() {
        return this->projection;
    }
    glm::vec3 getPosition() {
        return this->position;
    }
    glm::vec3 getFront() {
        return this->front;
    }
    glm::vec3 getUp() {
        return this->up;
    }
    glm::vec3 getRight() {
        return this->right;
    }
    glm::vec3 getWorldUp() {
        return this->worldUp;
    }
    float getYaw() {
        return this->yaw;
    }
    float getPitch() {
        return this->pitch;
    }
    float getMovementSpeed() {
        return this->movementSpeed;
    }
    float getMouseSensitivity() {
        return this->mouseSensitivity;
    }
    float getZoom() {
        return this->zoom;
    }
    float getLastX() {
        return this->lastX;
    }
    float getLastY() {
        return this->lastY;
    }
    bool getFirstMouse() {
        return this->firstMouse;
    }
    void setLastX(float lastX) {
        this->lastX = lastX;
    }
    void setLastY(float lastY) {
        this->lastY = lastY;
    }
    void setFirstMouse(bool firstMouse) {
        this->firstMouse = firstMouse;
    }
    float getScreenWidth() {
        return this->screenWidth;
    }
    float getScreenHeight() {
        return this->screenHeight;
    }
    float getNearPlane() {
        return this->nearPlane;
    }
    float getFarPlane() {
        return this->farPlane;
    }
    float getAspectRation() {
        return this->aspectRatio;
    }
};