#include "Renderer.hpp"

#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "InstanceBuffer.hpp"
#include "Mesh.hpp"
#include "ModelGameObject.hpp"
#include "ResourceManager.hpp"
#include "Skybox.hpp"
#include "TextureType.hpp"

#include <unordered_map>
#include <vector>

Renderer* Renderer::instance;

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

Renderer* Renderer::getInstance() {
    if (!instance) {
        instance = new Renderer();
    }
    return instance;
}

namespace {

template <typename T>
const std::shared_ptr<Shader>& getActiveShader(const T& data) {
    if (data.getShadingType() == SHADING_TYPE::PBR) {
        return data.getShaderPbr();
    }
    return data.getShaderPhong();
}

void setSharedUniforms(Shader& shader, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos, float time) {
    shader.setMatrix4f("uView", view);
    shader.setMatrix4f("uProjection", projection);
    shader.setVector3f("uViewPos", viewPos);
    shader.setFloat("uTime", time);
}

template <typename T>
void setMaterialUniforms(Shader& shader, const T& data) {
    const std::shared_ptr<Material>& material = data.getMaterial();
    if (material == nullptr) {
        return;
    }
    shader.setVector4f("uMaterial.albedo", material->albedo);
    shader.setVector3f("uMaterial.ambient", material->ambient);
    shader.setVector3f("uMaterial.diffuse", material->diffuse);
    shader.setVector3f("uMaterial.specular", material->specular);
    shader.setFloat("uMaterial.shininess", material->shininess);
}

template <typename T>
void setUseTextureUniforms(Shader& shader, const T& data) {
    shader.setBool("useTextureAlbedo", data.getUseTextureAlbedo());
    shader.setBool("useTextureDiffuse", data.getUseTextureDiffuse());
    shader.setBool("useTextureSpecular", data.getUseTextureSpecular());
    shader.setBool("useTextureNormal", data.getUseTextureNormal());
    shader.setBool("useTextureHeight", data.getUseTextureHeight());
    shader.setBool("useTextureRoughness", data.getUseTextureRoughness());
    shader.setBool("useTextureShininess", data.getUseTextureShininess());
    shader.setBool("useTextureMetalness", data.getUseTextureMetalness());
    shader.setBool("useTextureAmbientOcclusion", data.getUseTextureAmbientOcclusion());
}

template <typename T>
void bindTextures(const T& data) {
    if (data.getTextureAlbedo() != nullptr && data.getUseTextureAlbedo()) {
        data.getTextureAlbedo()->bind(TEXTURE_ALBEDO.index);
    }
    if (data.getTextureDiffuse() != nullptr && data.getUseTextureDiffuse()) {
        data.getTextureDiffuse()->bind(TEXTURE_DIFFUSE.index);
    }
    if (data.getTextureSpecular() != nullptr && data.getUseTextureSpecular()) {
        data.getTextureSpecular()->bind(TEXTURE_SPECULAR.index);
    }
    if (data.getTextureNormal() != nullptr && data.getUseTextureNormal()) {
        data.getTextureNormal()->bind(TEXTURE_NORMAL.index);
    }
    if (data.getTextureHeight() != nullptr && data.getUseTextureHeight()) {
        data.getTextureHeight()->bind(TEXTURE_HEIGHT.index);
    }
    if (data.getTextureRoughness() != nullptr && data.getUseTextureRoughness()) {
        data.getTextureRoughness()->bind(TEXTURE_ROUGHNESS.index);
    }
    if (data.getTextureShininess() != nullptr && data.getUseTextureShininess()) {
        data.getTextureShininess()->bind(TEXTURE_SHININESS.index);
    }
    if (data.getTextureMetalness() != nullptr && data.getUseTextureMetalness()) {
        data.getTextureMetalness()->bind(TEXTURE_METALNESS.index);
    }
    if (data.getTextureAmbientOcclusion() != nullptr && data.getUseTextureAmbientOcclusion()) {
        data.getTextureAmbientOcclusion()->bind(TEXTURE_AMBIENT_OCCLUSION.index);
    }
}

void setSamplerUniforms(Shader& shader) {
    shader.setInt(TEXTURE_ALBEDO.name, TEXTURE_ALBEDO.index);
    shader.setInt(TEXTURE_DIFFUSE.name, TEXTURE_DIFFUSE.index);
    shader.setInt(TEXTURE_SPECULAR.name, TEXTURE_SPECULAR.index);
    shader.setInt(TEXTURE_NORMAL.name, TEXTURE_NORMAL.index);
    shader.setInt(TEXTURE_HEIGHT.name, TEXTURE_HEIGHT.index);
    shader.setInt(TEXTURE_ROUGHNESS.name, TEXTURE_ROUGHNESS.index);
    shader.setInt(TEXTURE_SHININESS.name, TEXTURE_SHININESS.index);
    shader.setInt(TEXTURE_METALNESS.name, TEXTURE_METALNESS.index);
    shader.setInt(TEXTURE_AMBIENT_OCCLUSION.name, TEXTURE_AMBIENT_OCCLUSION.index);
}

void setLightUniforms(Shader& shader, const std::vector<std::shared_ptr<LightGameObject>>& lights) {
    for (const std::shared_ptr<LightGameObject>& light : lights) {
        if (light == nullptr || light->getLightDrawData() == nullptr) {
            continue;
        }
        const std::shared_ptr<LightDrawData>& lightDrawData = light->getLightDrawData();
        shader.setVector3f("uLight.position", light->getTransform().getPosition());
        if (lightDrawData->getLight() != nullptr) {
            shader.setVector4f("uLight.color", lightDrawData->getLight()->albedo);
            shader.setVector3f("uLight.ambient", lightDrawData->getLight()->ambient);
            shader.setVector3f("uLight.diffuse", lightDrawData->getLight()->diffuse);
            shader.setVector3f("uLight.specular", lightDrawData->getLight()->specular);
        }
    }
}

void drawMeshBuffers(const std::shared_ptr<Mesh>& mesh) {
    if (mesh == nullptr) {
        return;
    }
    for (const std::shared_ptr<Geometry>& geometry : mesh->getGeometryList()) {
        if (geometry == nullptr || geometry->getVertexArray() == nullptr) {
            continue;
        }
        geometry->getVertexArray()->bind();
        if (geometry->getIsIndexed() && geometry->getIndexBuffer() != nullptr) {
            glDrawElements(GL_TRIANGLES, geometry->getRawIndexDataCount(), GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, geometry->getStructuredVertexDataCount());
        }
    }
    glBindVertexArray(0);
}

std::vector<InstanceData> buildInstanceData(const std::vector<const Transform*>& transforms) {
    std::vector<InstanceData> instanceData;
    instanceData.reserve(transforms.size());
    for (const Transform* transform : transforms) {
        InstanceData data;
        data.model = transform->getModelMatrix();
        data.inverseModel = transform->getInverseModelMatrix();
        instanceData.push_back(data);
    }
    return instanceData;
}

template <typename T>
void submitSingle(const T& data, const Transform& transform, const glm::mat4& view, const glm::mat4& projection,
                  const glm::vec3& viewPos, float time, const std::vector<std::shared_ptr<LightGameObject>>& lights,
                  Renderer::Stats& stats) {
    const std::shared_ptr<Shader>& shader = getActiveShader(data);
    if (shader == nullptr || shader->getShaderProgram() == 0) {
        return;
    }
    shader->bind();
    shader->setBool("uInstancing", false);
    setSharedUniforms(*shader, view, projection, viewPos, time);
    setMaterialUniforms(*shader, data);
    setUseTextureUniforms(*shader, data);
    setSamplerUniforms(*shader);
    setLightUniforms(*shader, lights);
    shader->setMatrix4f("uModel", transform.getModelMatrix());
    shader->setMatrix4f("uInverseModel", transform.getInverseModelMatrix());
    bindTextures(data);
    drawMeshBuffers(data.getMesh());
    stats.drawCalls++;
    stats.drawn++;
}

template <typename T>
void submitInstanced(const T& data, const std::vector<const Transform*>& transforms, const glm::mat4& view,
                     const glm::mat4& projection, const glm::vec3& viewPos, float time,
                     const std::vector<std::shared_ptr<LightGameObject>>& lights, Renderer::Stats& stats) {
    const std::shared_ptr<Shader>& shader = getActiveShader(data);
    if (shader == nullptr || shader->getShaderProgram() == 0) {
        return;
    }
    const std::shared_ptr<Mesh>& mesh = data.getMesh();
    if (mesh == nullptr) {
        return;
    }
    const std::vector<InstanceData> instanceData = buildInstanceData(transforms);
    const GLsizei instanceCount = static_cast<GLsizei>(instanceData.size());

    shader->bind();
    shader->setBool("uInstancing", true);
    setSharedUniforms(*shader, view, projection, viewPos, time);
    setMaterialUniforms(*shader, data);
    setUseTextureUniforms(*shader, data);
    setSamplerUniforms(*shader);
    setLightUniforms(*shader, lights);
    bindTextures(data);

    for (const std::shared_ptr<Geometry>& geometry : mesh->getGeometryList()) {
        if (geometry == nullptr || geometry->getVertexArray() == nullptr || geometry->getInstanceBuffer() == nullptr) {
            continue;
        }
        geometry->getInstanceBuffer()->upload(instanceData.data(), instanceData.size() * sizeof(InstanceData));
        geometry->getVertexArray()->bind();
        if (geometry->getIsIndexed() && geometry->getIndexBuffer() != nullptr) {
            glDrawElementsInstanced(GL_TRIANGLES, geometry->getRawIndexDataCount(), GL_UNSIGNED_INT, 0, instanceCount);
        }
        else {
            glDrawArraysInstanced(GL_TRIANGLES, 0, geometry->getStructuredVertexDataCount(), instanceCount);
        }
    }
    glBindVertexArray(0);
    stats.drawCalls++;
    stats.instances += instanceCount;
    stats.drawn += instanceCount;
}

} // namespace

void Renderer::beginFrame(const Camera& camera) {
    this->stats = Stats{};
    this->frame.view = camera.getView();
    this->frame.projection = camera.getProjection();
    this->frame.viewPos = camera.getPosition();
    this->frame.time = static_cast<float>(glfwGetTime());
    this->frustum.update(this->frame.projection * this->frame.view);
}

bool Renderer::isVisible(const Transform& transform) const {
    if (!this->frustum.testSphere(transform.getWorldCenter(), transform.getWorldRadius())) {
        return false;
    }
    return this->frustum.testAABB(transform.getWorldAABBMin(), transform.getWorldAABBMax());
}

void Renderer::draw(const std::shared_ptr<DrawData>& drawData, const Transform& transform, const Camera& camera) {
    const std::vector<std::shared_ptr<LightGameObject>>& lights = GameObjectManager::getInstance()->getLightGameObjectList();
    if (drawData != nullptr) {
        submitSingle(*drawData, transform, this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time, lights, this->stats);
    }
}

void Renderer::drawModel(const std::shared_ptr<ModelDrawData>& modelDrawData, const Transform& transform, const Camera& camera) {
    const std::vector<std::shared_ptr<LightGameObject>>& lights = GameObjectManager::getInstance()->getLightGameObjectList();
    if (modelDrawData != nullptr) {
        submitSingle(*modelDrawData, transform, this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time, lights, this->stats);
    }
}

void Renderer::drawInstanced(const std::shared_ptr<DrawData>& drawData, const std::vector<const Transform*>& transforms, const Camera& camera) {
    const std::vector<std::shared_ptr<LightGameObject>>& lights = GameObjectManager::getInstance()->getLightGameObjectList();
    if (drawData != nullptr && !transforms.empty()) {
        submitInstanced(*drawData, transforms, this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time, lights, this->stats);
    }
}

void Renderer::drawInstancedModel(const std::shared_ptr<ModelDrawData>& modelDrawData, const std::vector<const Transform*>& transforms, const Camera& camera) {
    const std::vector<std::shared_ptr<LightGameObject>>& lights = GameObjectManager::getInstance()->getLightGameObjectList();
    if (modelDrawData != nullptr && !transforms.empty()) {
        submitInstanced(*modelDrawData, transforms, this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time, lights, this->stats);
    }
}

void Renderer::drawLight(const std::shared_ptr<LightGameObject>& lightGameObject, const Camera& camera) {
    if (lightGameObject == nullptr || lightGameObject->getLightDrawData() == nullptr) {
        return;
    }
    const std::shared_ptr<LightDrawData>& lightDrawData = lightGameObject->getLightDrawData();
    const std::shared_ptr<Shader>& shader = lightDrawData->getShader();
    if (shader == nullptr || shader->getShaderProgram() == 0) {
        return;
    }
    const Transform& transform = lightGameObject->getTransform();
    shader->bind();
    shader->setBool("uInstancing", false);
    setSharedUniforms(*shader, this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time);
    shader->setMatrix4f("uModel", transform.getModelMatrix());
    shader->setMatrix4f("uInverseModel", transform.getInverseModelMatrix());
    if (lightDrawData->getLight() != nullptr) {
        shader->setVector4f("uColor", lightDrawData->getLight()->albedo);
    }
    drawMeshBuffers(lightDrawData->getMesh());
    this->stats.drawCalls++;
    this->stats.drawn++;
}

void Renderer::drawSkybox(const Camera& camera) {
    const std::shared_ptr<Skybox> skybox = ResourceManager::getInstance()->getSkyboxByName("skybox");
    if (skybox == nullptr || skybox->getShader() == nullptr || skybox->getMesh() == nullptr) {
        return;
    }
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);

    const glm::mat4 view = glm::mat4(glm::mat3(camera.getView()));
    const std::shared_ptr<Shader>& shader = skybox->getShader();
    shader->bind();
    shader->setMatrix4f("uView", view);
    shader->setMatrix4f("uProjection", camera.getProjection());
    shader->setInt("uSkybox", 0);
    shader->setVector4f("uColor", glm::vec4(skybox->getColorX(), skybox->getColorY(), skybox->getColorZ(), 1.0f));
    shader->setFloat("uTime", this->frame.time);

    for (const std::shared_ptr<Geometry>& geometry : skybox->getMesh()->getGeometryList()) {
        if (geometry == nullptr || geometry->getVertexArray() == nullptr) {
            continue;
        }
        if (skybox->getCubeMap() != nullptr) {
            skybox->getCubeMap()->bind(0);
        }
        geometry->getVertexArray()->bind();
        if (geometry->getIsIndexed() && geometry->getIndexBuffer() != nullptr) {
            glDrawElements(GL_TRIANGLES, geometry->getRawIndexDataCount(), GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, geometry->getStructuredVertexDataCount());
        }
    }
    glBindVertexArray(0);
    if (skybox->getCubeMap() != nullptr) {
        skybox->getCubeMap()->unbind();
    }
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    this->stats.drawCalls++;
}

void Renderer::drawAll(const Camera& camera) {
    const std::vector<std::shared_ptr<LightGameObject>>& lights = GameObjectManager::getInstance()->getLightGameObjectList();

    std::unordered_map<const DrawData*, std::vector<const Transform*>> batches;
    for (const std::shared_ptr<GameObject>& gameObject : GameObjectManager::getInstance()->getGameObjectList()) {
        if (gameObject == nullptr) {
            continue;
        }
        const Transform& transform = gameObject->getTransform();
        if (!this->isVisible(transform)) {
            this->stats.culled++;
            continue;
        }
        batches[gameObject->getDrawData().get()].push_back(&transform);
    }

    for (const auto& entry : batches) {
        const DrawData* drawData = entry.first;
        const std::vector<const Transform*>& transforms = entry.second;
        if (drawData == nullptr || transforms.empty()) {
            continue;
        }
        if (transforms.size() > 1) {
            submitInstanced(*drawData, transforms, this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time, lights, this->stats);
        }
        else {
            submitSingle(*drawData, *transforms.front(), this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time, lights, this->stats);
        }
    }
}

void Renderer::drawAllModels(const Camera& camera) {
    const std::vector<std::shared_ptr<LightGameObject>>& lights = GameObjectManager::getInstance()->getLightGameObjectList();

    std::unordered_map<const ModelDrawData*, std::vector<const Transform*>> batches;
    for (const std::shared_ptr<ModelGameObject>& modelGameObject : GameObjectManager::getInstance()->getModelGameObjectList()) {
        if (modelGameObject == nullptr) {
            continue;
        }
        const Transform& transform = modelGameObject->getTransform();
        if (!this->isVisible(transform)) {
            this->stats.culled++;
            continue;
        }
        batches[modelGameObject->getModelDrawData().get()].push_back(&transform);
    }

    for (const auto& entry : batches) {
        const ModelDrawData* modelDrawData = entry.first;
        const std::vector<const Transform*>& transforms = entry.second;
        if (modelDrawData == nullptr || transforms.empty()) {
            continue;
        }
        if (transforms.size() > 1) {
            submitInstanced(*modelDrawData, transforms, this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time, lights, this->stats);
        }
        else {
            submitSingle(*modelDrawData, *transforms.front(), this->frame.view, this->frame.projection, this->frame.viewPos, this->frame.time, lights, this->stats);
        }
    }
}

void Renderer::drawAllLights(const Camera& camera) {
    for (const std::shared_ptr<LightGameObject>& lightGameObject : GameObjectManager::getInstance()->getLightGameObjectList()) {
        this->drawLight(lightGameObject, camera);
    }
}

void Renderer::colorBackground(const glm::vec4& color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
