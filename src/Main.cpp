#include "Application.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

int main() {
    Application* application = Application::getInstance(800, 600, "3D Template");
    application->run();
    delete application;
    return 0;
}
