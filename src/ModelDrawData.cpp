#include "ModelDrawData.hpp"

#include "ResourceManager.hpp"

ModelDrawData::ModelDrawData() {
    this->guid = Util::generateGUID();
    this->name = "";
    this->path = "";
    this->directory = "";
    this->gammaCorrection = false;
    this->mesh = std::make_shared<Mesh>();
    this->material = std::make_shared<Material>();
    this->shaderPhong = shaderPhong;
    this->shaderPBR = shaderPBR;
    this->tempGeometryList =  std::vector<std::shared_ptr<Geometry>>();
    this->useTextureAlbedo = true;
    this->useTextureDiffuse = true;
    this->useTextureSpecular = true;
    this->useTextureNormal = true;
    this->useTextureHeight = false;
    this->useTextureRoughness = false;
    this->useTextureShininess = false;
    this->useTextureMetalness = false;
    this->useTextureAmbientOcclusion = false;
    this->updateShaderTextures();
}


ModelDrawData::ModelDrawData(const std::string& name, const std::string& path, std::shared_ptr<Material> material,
                             std::shared_ptr<Shader> shaderPhong, std::shared_ptr<Shader> shaderPBR,
                             bool useTextureAlbedo,
        bool useTextureDiffuse,
        bool useTextureSpecular,
        bool useTextureNormal,
        bool useTextureHeight,
        bool useTextureRoughness,
        bool useTextureShininess,
        bool useTextureMetalness,
        bool useTextureAmbientOcclusion,
        SHADING_TYPE shadingType) {
    this->guid = Util::generateGUID();
    this->name = name;
    std::filesystem::path temp = ResourceManager::getInstance()->getAssetPath(path);
    this->path = temp.string();
    this->directory = temp.parent_path().string();
    this->gammaCorrection = false;
    this->mesh = std::make_shared<Mesh>(name + "Mesh");
    this->material = material;
    this->shaderPhong = shaderPhong;
    this->shaderPBR = shaderPBR;
    this->tempGeometryList =  std::vector<std::shared_ptr<Geometry>>();
    this->useTextureAlbedo = useTextureAlbedo;
    this->useTextureDiffuse = useTextureDiffuse;
    this->useTextureSpecular = useTextureSpecular;
    this->useTextureNormal = useTextureNormal;
    this->useTextureHeight = useTextureHeight;
    this->useTextureRoughness = useTextureRoughness;
    this->useTextureShininess = useTextureShininess;
    this->useTextureMetalness = useTextureMetalness;
    this->useTextureAmbientOcclusion = useTextureAmbientOcclusion;
    this->shadingType = shadingType;
    this->loadAssimpModel(this->path);
    this->updateShaderTextures();
}


ModelDrawData::~ModelDrawData() {

}

void ModelDrawData::loadAssimpModel(const std::string& path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    // Load materials/textures once
    for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* aiMat = scene->mMaterials[i];
        this->loadMaterialTextures(aiMat, aiTextureType_BASE_COLOR);
        this->loadMaterialTextures(aiMat, aiTextureType_DIFFUSE);
        this->loadMaterialTextures(aiMat, aiTextureType_SPECULAR);
        this->loadMaterialTextures(aiMat, aiTextureType_NORMALS);
        this->loadMaterialTextures(aiMat, aiTextureType_HEIGHT);
        this->loadMaterialTextures(aiMat, aiTextureType_DIFFUSE_ROUGHNESS);
        this->loadMaterialTextures(aiMat, aiTextureType_SHININESS);
        this->loadMaterialTextures(aiMat, aiTextureType_METALNESS);
        this->loadMaterialTextures(aiMat, aiTextureType_AMBIENT_OCCLUSION);
    }

    this->processAssimpModelNode(scene->mRootNode, scene);
    this->mesh->setGeometryList(tempGeometryList);
}

void ModelDrawData::processAssimpModelNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->tempGeometryList.push_back(this->processAssimpMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        this->processAssimpModelNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Geometry> ModelDrawData::processAssimpMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<GeometryVertex> vertices;
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        GeometryVertex vertex;
        glm::vec4 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = glm::vec3(vector.x, vector.y, vector.z);
        if (mesh->GetNumColorChannels() > 0 && mesh->mColors[0] != nullptr) {
            vector.x = mesh->mColors[0][i].r;
            vector.y = mesh->mColors[0][i].g;
            vector.z = mesh->mColors[0][i].b;
            vector.w = mesh->mColors[0][i].a;
            vertex.color = vector;
        }
        else {
            vertex.color = glm::vec4(1.0f);
        }
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = glm::vec3(vector.x, vector.y, vector.z);
        }
        else {
            vertex.normal = glm::vec3(1.0f);
        }
        if (mesh->mTextureCoords[0]) {
            vector.x = mesh->mTextureCoords[0][i].x;
            vector.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = glm::vec2(vector.x, vector.y);
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = glm::vec3(vector.x, vector.y, vector.z);
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = glm::vec3(vector.x, vector.y, vector.z);
        }
        else {
            vertex.uv = glm::vec2(1.0f);
            vertex.tangent = glm::vec3(1.0f);
            vertex.bitangent = glm::vec3(1.0f);
        }

        /*if (mesh->HasBones()) {
            for (unsigned int boneIndex = 0; boneIndex < mesh->mNumBones; boneIndex++) {
                aiBone* bone = mesh->mBones[boneIndex];
                unsigned int boneId = boneIndex;

                for (unsigned int w = 0; w < bone->mNumWeights; w++) {
                    aiVertexWeight weight = bone->mWeights[w];
                    unsigned int vertexId = weight.mVertexId;
                    float weightValue = weight.mWeight;

                    GeometryVertex& v = vertices[vertexId];

                    // Assign to the first available slot (max 4)
                    for (int i = 0; i < Util::MAX_BONE_INFLUENCE; i++) {
                        if (v.weights[i] == 0.0f) {
                            v.boneIds[i] = static_cast<float>(boneId);
                            v.weights[i] = weightValue;
                            break;
                        }
                    }
                }
            }
        }*/
        vertex.boneIds = glm::vec4(0.0f);
        vertex.weights = glm::vec4(0.0f);
        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>(!indices.empty(), vertices, indices);
    return geometry;
}

void ModelDrawData::loadMaterialTextures(aiMaterial* aiMaterial, aiTextureType type) {
    std::string textureName;
    TextureType textureType = Texture::assimpToRegularTextureType(type);
    for (unsigned int i = 0; i < aiMaterial->GetTextureCount(type); i++) {
        aiString texturePath;
        auto res = aiMaterial->GetTexture(type, i, &texturePath);
        std::string fullTexturePath = this->directory + "/" + texturePath.C_Str();
        if (res == AI_SUCCESS) {
            std::shared_ptr<Texture> texture = std::make_shared<Texture>(fullTexturePath, textureType);
            texture->setName(texture->getType().name + "0");

            if (textureType.name == "textureAlbedo") {
                this->textureAlbedo = texture;
            }
            else if (textureType.name == "textureDiffuse") {
                this->textureDiffuse = texture;
            }
            else if (textureType.name == "textureSpecular") {
                this->textureSpecular = texture;
            }
            else if (textureType.name == "textureNormal") {
                this->textureNormal = texture;
            }
            else if (textureType.name == "textureHeight") {
                this->textureHeight = texture;
            }
            else if (textureType.name == "textureRoughness") {
                this->textureRoughness = texture;
            }
            else if (textureType.name == "textureShininess") {
                this->textureShininess = texture;
            }
            else if (textureType.name == "textureMetalness") {
                this->textureMetalness = texture;
            }
            else if (textureType.name == "textureAmbientOcclusion") {
                this->textureAmbientOcclusion = texture;
            }

        }
    }
}

void ModelDrawData::updateShaderTextures() {
    this->shaderPhong->setBool("useTextureAlbedo", this->useTextureAlbedo);
    this->shaderPhong->setInt(TEXTURE_ALBEDO.name, TEXTURE_ALBEDO.index);
    this->shaderPhong->setBool("useTextureDiffuse", this->useTextureDiffuse);
    this->shaderPhong->setInt(TEXTURE_DIFFUSE.name, TEXTURE_DIFFUSE.index);
    this->shaderPhong->setBool("useTextureSpecular", this->useTextureSpecular);
    this->shaderPhong->setInt(TEXTURE_SPECULAR.name, TEXTURE_SPECULAR.index);
    this->shaderPhong->setBool("useTextureNormal", this->useTextureNormal);
    this->shaderPhong->setInt(TEXTURE_NORMAL.name, TEXTURE_NORMAL.index);
    this->shaderPhong->setBool("useTextureHeight", this->useTextureHeight);
    this->shaderPhong->setInt(TEXTURE_HEIGHT.name, TEXTURE_HEIGHT.index);
    this->shaderPhong->setBool("useTextureRoughness", this->useTextureRoughness);
    this->shaderPhong->setInt(TEXTURE_ROUGHNESS.name, TEXTURE_ROUGHNESS.index);
    this->shaderPhong->setBool("useTextureShininess", this->useTextureShininess);
    this->shaderPhong->setInt(TEXTURE_SHININESS.name, TEXTURE_SHININESS.index);
    this->shaderPhong->setBool("useTextureMetalness", this->useTextureMetalness);
    this->shaderPhong->setInt(TEXTURE_METALNESS.name, TEXTURE_METALNESS.index);
    this->shaderPhong->setBool("useTextureAmbientOcclusion", this->useTextureAmbientOcclusion);
    this->shaderPhong->setInt(TEXTURE_AMBIENT_OCCLUSION.name, TEXTURE_AMBIENT_OCCLUSION.index);

    this->shaderPBR->setBool("useTextureAlbedo", this->useTextureAlbedo);
    this->shaderPBR->setInt(TEXTURE_ALBEDO.name, TEXTURE_ALBEDO.index);
    this->shaderPBR->setBool("useTextureDiffuse", this->useTextureDiffuse);
    this->shaderPBR->setInt(TEXTURE_DIFFUSE.name, TEXTURE_DIFFUSE.index);
    this->shaderPBR->setBool("useTextureSpecular", this->useTextureSpecular);
    this->shaderPBR->setInt(TEXTURE_SPECULAR.name, TEXTURE_SPECULAR.index);
    this->shaderPBR->setBool("useTextureNormal", this->useTextureNormal);
    this->shaderPBR->setInt(TEXTURE_NORMAL.name, TEXTURE_NORMAL.index);
    this->shaderPBR->setBool("useTextureHeight", this->useTextureHeight);
    this->shaderPBR->setInt(TEXTURE_HEIGHT.name, TEXTURE_HEIGHT.index);
    this->shaderPBR->setBool("useTextureRoughness", this->useTextureRoughness);
    this->shaderPBR->setInt(TEXTURE_ROUGHNESS.name, TEXTURE_ROUGHNESS.index);
    this->shaderPBR->setBool("useTextureShininess", this->useTextureShininess);
    this->shaderPBR->setInt(TEXTURE_SHININESS.name, TEXTURE_SHININESS.index);
    this->shaderPBR->setBool("useTextureMetalness", this->useTextureMetalness);
    this->shaderPBR->setInt(TEXTURE_METALNESS.name, TEXTURE_METALNESS.index);
    this->shaderPBR->setBool("useTextureAmbientOcclusion", this->useTextureAmbientOcclusion);
    this->shaderPBR->setInt(TEXTURE_AMBIENT_OCCLUSION.name, TEXTURE_AMBIENT_OCCLUSION.index);
}
