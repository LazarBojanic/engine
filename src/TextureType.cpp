#include "TextureType.hpp"

TextureType::TextureType() {
    this->index = 0;
    this->name = "textureAlbedo";
}

TextureType::TextureType(int index, const std::string& name) {
    this->index = index;
    this->name = name;
}

TextureType::~TextureType() {

}



