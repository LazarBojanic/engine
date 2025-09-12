#include "Camera.hpp"

#include "Window.hpp"

Camera::Camera(glm::vec3 position, float width, float height, float nearPlane, float farPlane) {
    this->position = position;
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->movementSpeed = 30.0f;
    this->mouseSensitivity = 0.6f;
    this->zoom = 45.0f;
    this->screenWidth = width;
    this->screenHeight = height;
    this->aspectRatio = screenWidth / screenHeight;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    this->lastX = width;
    this->lastY = height;
    this->firstMouse = true;
    this->updateProjection();
    this->updateView();
}
Camera::Camera(float positionX, float positionY, float positionZ, float width, float height, float nearPlane, float farPlane) {
    this->position = glm::vec3(positionX, positionY, positionZ);
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->movementSpeed = 0.6f;
    this->mouseSensitivity = 1.0f;
    this->zoom = 45.0f;
    this->screenWidth = width;
    this->screenHeight = height;
    this->aspectRatio = screenWidth / screenHeight;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    this->lastX = width;
    this->lastY = height;
    this->firstMouse = true;
    this->updateProjection();
    this->updateView();
}
Camera::~Camera(){
}

void Camera::updateView() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
    this->view = glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::updateProjection() {
    this->projection = glm::perspective(glm::radians(zoom), aspectRatio, nearPlane, farPlane);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime){
    float velocity = this->movementSpeed * deltaTime;
    if (direction == FORWARD) {
        this->position += this->front * velocity;
    }       
    if (direction == BACKWARD) {
        this->position -= this->front * velocity;
    }       
    if (direction == LEFT) {
        this->position -= this->right * velocity;
    }       
    if (direction == RIGHT) {
        this->position += this->right * velocity;
    }
    if (direction == UP) {
        this->position += this->worldUp * velocity;
    }
    if (direction == DOWN) {
        this->position -= this->worldUp * velocity;
    }
    updateView();
}
void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= this->mouseSensitivity;
    yoffset *= this->mouseSensitivity;
    this->yaw += xoffset;
    this->pitch += yoffset;
    if (constrainPitch) {
        if (this->pitch > 89.0f) {
            this->pitch = 89.0f;
        }
        if (this->pitch < -89.0f) {
            this->pitch = -89.0f;
        }
    }
    updateView();
}
void Camera::processMouseScroll(float yoffset){
    this->zoom -= yoffset;
    if (this->zoom < 1.0f) {
        this->zoom = 1.0f;
    }      
    if (this->zoom > 45.0f) {
        this->zoom = 45.0f;
    }
    updateProjection();
}