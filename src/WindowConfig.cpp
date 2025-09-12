
#include "WindowConfig.hpp"

WindowConfig::WindowConfig() {
    this->posX = 600;
    this->posY = 300;
    this->width = 800;
    this->height = 600;
    this->title = "2D Template";
    this->fullscreen = false;
    this->vsync = true;
    this->resizable = false;
}

WindowConfig::WindowConfig(int width, int height, const std::string& title) {
    this->posX = 600;
    this->posY = 300;
    this->width = width;
    this->height = height;
    this->title = title;
    this->fullscreen = false;
    this->vsync = true;
    this->resizable = false;
}

WindowConfig::~WindowConfig() {
}
