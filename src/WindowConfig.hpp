#pragma once
#include <string>

class WindowConfig {
public:
    int posX;
    int posY;
    int width;
    int height;
    std::string title;
    bool fullscreen;
    bool vsync;
    bool resizable;
    WindowConfig();
    WindowConfig(int width, int height, const std::string& title);
    ~WindowConfig();
};
