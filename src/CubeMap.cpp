
#include "CubeMap.hpp"

#include "ResourceManager.hpp"

CubeMap::CubeMap() {
    this->guid = Util::generateGUID();
    this->cubeMapId = 0;
    this->name = "";
    this->mode = GL_TEXTURE_CUBE_MAP;
    this->width = 800;
    this->height = 600;
    this->format = GL_RGBA;
    this->wrap_S = GL_CLAMP_TO_EDGE;
    this->wrap_T = GL_CLAMP_TO_EDGE;
    this->wrap_R = GL_CLAMP_TO_EDGE;
    this->filterMin = GL_LINEAR;
    this->filterMax = GL_LINEAR;
    this->facePaths = std::vector<std::string>();
}

CubeMap::CubeMap(const std::string& name, std::vector<std::string> facePaths) {
    this->guid = Util::generateGUID();
    this->name = name;
    this->mode = GL_TEXTURE_CUBE_MAP;
    this->wrap_S = GL_CLAMP_TO_EDGE;
    this->wrap_T = GL_CLAMP_TO_EDGE;
    this->wrap_R = GL_CLAMP_TO_EDGE;
    this->filterMin = GL_LINEAR;
    this->filterMax = GL_LINEAR;
    this->facePaths = std::vector<std::string>();
    for (auto& facePath : facePaths) {
        this->facePaths.push_back(ResourceManager::getInstance()->getAssetPath(facePath).string());
    }
	generate(this->facePaths);
}

CubeMap::~CubeMap() {
    glDeleteTextures(1, &this->cubeMapId);
}

void CubeMap::bind(unsigned int textureChannel) {
	glActiveTexture(GL_TEXTURE0 + textureChannel);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubeMapId);
}

void CubeMap::unbind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
void CubeMap::generate(std::vector<std::string> facePaths) {
    glGenTextures(1, &this->cubeMapId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubeMapId);
    int tempWidth, tempHeight, tempNumberOfChannels;
    for (unsigned int i = 0; i < facePaths.size(); i++) {
        stbi_set_flip_vertically_on_load(false);
        unsigned char* data = stbi_load(facePaths.at(i).c_str(), &tempWidth, &tempHeight, &tempNumberOfChannels, 0);
        if (data) {
            if (tempNumberOfChannels == 1) {
                this->format = GL_RED;
            }
            else if (tempNumberOfChannels == 2) {
                this->format = GL_RG;
            }
            else if (tempNumberOfChannels == 3) {
                this->format = GL_RGB;
            }
            else if (tempNumberOfChannels == 4) {
                this->format = GL_RGBA;
            }
            this->width = tempWidth;
            this->height = tempHeight;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, this->format, this->width, this->height, 0, this->format, GL_UNSIGNED_BYTE, data);
            glTexParameteri(this->mode, GL_TEXTURE_MIN_FILTER, this->filterMin);
            glTexParameteri(this->mode, GL_TEXTURE_MAG_FILTER, this->filterMax);
            glTexParameteri(this->mode, GL_TEXTURE_WRAP_S, this->wrap_S);
            glTexParameteri(this->mode, GL_TEXTURE_WRAP_T, this->wrap_T);
            glTexParameteri(this->mode, GL_TEXTURE_WRAP_R, this->wrap_R);
            stbi_image_free(data);
        }
        else {
            std::cout << "CubeMap texture failed to load at path: " << facePaths.at(i) << std::endl;
            stbi_image_free(data);
        }
    }
}