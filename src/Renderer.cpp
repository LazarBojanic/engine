#include "Renderer.hpp"

#include "Application.hpp"
#include "LightGameObject.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"


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

void Renderer::draw(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Camera> camera, bool scaled) {
    //glEnable(GL_CULL_FACE);
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(gameObject->getPositionX(), gameObject->getPositionY(), gameObject->getPositionZ()));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(gameObject->getRotationX()), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(gameObject->getRotationY()), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(gameObject->getRotationZ()), glm::vec3(0.0f, 0.0f, 1.0f));
    if (!scaled) {
        modelMatrix = glm::scale(modelMatrix, glm::vec3(gameObject->getSizeX(), gameObject->getSizeY(), gameObject->getSizeZ()));
    }
    else {
        modelMatrix = glm::scale(modelMatrix, glm::vec3(gameObject->getScaledSizeX(), gameObject->getScaledSizeY(), gameObject->getScaledSizeZ()));
    }
    glm::mat4 inverseModelMatrix = glm::transpose(glm::inverse(modelMatrix));
    glm::mat4 viewMatrix = camera->getView();
    glm::mat4 projectionMatrix = camera->getProjection();
    gameObject->updateShaderViewData(modelMatrix, inverseModelMatrix, viewMatrix, projectionMatrix, camera->getPosition());
    gameObject->updateShaderMaterial();
    gameObject->updateShaderUseTexture();
    for (auto lightGameObject : GameObjectManager::getInstance()->getLightGameObjectList()) {
        gameObject->updateShaderLight(lightGameObject);
    }
    gameObject->updateShaderTime(glfwGetTime());
    if (gameObject->getDrawData()->getShaderPhong() != nullptr && gameObject->getDrawData()->getShadingType() == SHADING_TYPE::PHONG) {
        gameObject->getDrawData()->getShaderPhong()->bind();
    }
    else if (gameObject->getDrawData()->getShaderPbr() != nullptr && gameObject->getDrawData()->getShadingType() == SHADING_TYPE::PBR) {
        gameObject->getDrawData()->getShaderPbr()->bind();
    }

    if (gameObject->getDrawData()->getTextureAlbedo() != nullptr && gameObject->getDrawData()->getUseTextureAlbedo()) {
            gameObject->getDrawData()->getTextureAlbedo()->bind(gameObject->getDrawData()->getTextureAlbedo()->getType().index);
    }
    if (gameObject->getDrawData()->getTextureDiffuse() != nullptr && gameObject->getDrawData()->getUseTextureDiffuse()) {
        gameObject->getDrawData()->getTextureDiffuse()->bind(gameObject->getDrawData()->getTextureDiffuse()->getType().index);
    }
    if (gameObject->getDrawData()->getTextureSpecular() != nullptr && gameObject->getDrawData()->getUseTextureSpecular()) {
        gameObject->getDrawData()->getTextureSpecular()->bind(gameObject->getDrawData()->getTextureSpecular()->getType().index);
    }
    if (gameObject->getDrawData()->getTextureNormal() != nullptr && gameObject->getDrawData()->getUseTextureNormal()) {
        gameObject->getDrawData()->getTextureNormal()->bind(gameObject->getDrawData()->getTextureNormal()->getType().index);
    }
    if (gameObject->getDrawData()->getTextureHeight() != nullptr && gameObject->getDrawData()->getUseTextureHeight()) {
        gameObject->getDrawData()->getTextureHeight()->bind(gameObject->getDrawData()->getTextureHeight()->getType().index);
    }
    if (gameObject->getDrawData()->getTextureRoughness() != nullptr && gameObject->getDrawData()->getUseTextureRoughness()) {
        gameObject->getDrawData()->getTextureRoughness()->bind(gameObject->getDrawData()->getTextureRoughness()->getType().index);
    }
    if (gameObject->getDrawData()->getTextureShininess() != nullptr && gameObject->getDrawData()->getUseTextureShininess()) {
        gameObject->getDrawData()->getTextureShininess()->bind(gameObject->getDrawData()->getTextureShininess()->getType().index);
    }
    if (gameObject->getDrawData()->getTextureMetalness() != nullptr && gameObject->getDrawData()->getUseTextureMetalness()) {
        gameObject->getDrawData()->getTextureMetalness()->bind(gameObject->getDrawData()->getTextureMetalness()->getType().index);
    }
    if (gameObject->getDrawData()->getTextureAmbientOcclusion() != nullptr && gameObject->getDrawData()->getUseTextureAmbientOcclusion()) {
        gameObject->getDrawData()->getTextureAmbientOcclusion()->bind(gameObject->getDrawData()->getTextureAmbientOcclusion()->getType().index);
    }
    
    for (auto geometry : gameObject->getDrawData()->getMesh()->getGeometryList()) {
        geometry->getVertexArray()->bind();
        geometry->getVertexBuffer()->bind();
        

        if (geometry->getIsIndexed()) {
            geometry->getIndexBuffer()->bind();
            glDrawElements(GL_TRIANGLES, geometry->getRawIndexDataCount(), GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, geometry->getStructuredVertexDataCount());
        }
        geometry->getVertexArray()->unbind();
        geometry->getVertexBuffer()->unbind();
        geometry->getIndexBuffer()->unbind();
    }
    if (gameObject->getDrawData()->getShaderPhong() != nullptr) {
        gameObject->getDrawData()->getShaderPhong()->unbind();
    }
    else if (gameObject->getDrawData()->getShaderPbr() != nullptr) {
        gameObject->getDrawData()->getShaderPbr()->unbind();
    }
    //glDisable(GL_CULL_FACE);
}

void Renderer::drawModel(std::shared_ptr<ModelGameObject> modelGameObject, std::shared_ptr<Camera> camera, bool scaled) {
    //glEnable(GL_CULL_FACE);
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(modelGameObject->getPositionX(), modelGameObject->getPositionY(), modelGameObject->getPositionZ()));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(modelGameObject->getRotationX()), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(modelGameObject->getRotationY()), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(modelGameObject->getRotationZ()), glm::vec3(0.0f, 0.0f, 1.0f));
    if (!scaled) {
        modelMatrix = glm::scale(modelMatrix, glm::vec3(modelGameObject->getSizeX(), modelGameObject->getSizeY(), modelGameObject->getSizeZ()));
    }
    else {
        modelMatrix = glm::scale(modelMatrix, glm::vec3(modelGameObject->getScaledSizeX(), modelGameObject->getScaledSizeY(), modelGameObject->getScaledSizeZ()));
    }
    glm::mat4 inverseModelMatrix = glm::transpose(glm::inverse(modelMatrix));
    glm::mat4 viewMatrix = camera->getView();
    glm::mat4 projectionMatrix = camera->getProjection();
    modelGameObject->updateShaderViewData(modelMatrix, inverseModelMatrix, viewMatrix, projectionMatrix, camera->getPosition());
    modelGameObject->updateShaderMaterial();
    modelGameObject->updateShaderUseTexture();
    for (auto lightGameObject : GameObjectManager::getInstance()->getLightGameObjectList()) {
        modelGameObject->updateShaderLight(lightGameObject);
    }
    modelGameObject->updateShaderTime(glfwGetTime());
    if (modelGameObject->getModelDrawData()->getShaderPhong() != nullptr && modelGameObject->getModelDrawData()->getShadingType() == SHADING_TYPE::PHONG) {
        modelGameObject->getModelDrawData()->getShaderPhong()->bind();
    }
    else if (modelGameObject->getModelDrawData()->getShaderPbr() != nullptr && modelGameObject->getModelDrawData()->getShadingType() == SHADING_TYPE::PBR) {
        modelGameObject->getModelDrawData()->getShaderPbr()->bind();
    }

    if (modelGameObject->getModelDrawData()->getTextureAlbedo() != nullptr && modelGameObject->getModelDrawData()->getUseTextureAlbedo()) {
        modelGameObject->getModelDrawData()->getTextureAlbedo()->bind(modelGameObject->getModelDrawData()->getTextureAlbedo()->getType().index);
    }
    if (modelGameObject->getModelDrawData()->getTextureDiffuse() != nullptr && modelGameObject->getModelDrawData()->getUseTextureDiffuse()) {
        modelGameObject->getModelDrawData()->getTextureDiffuse()->bind(modelGameObject->getModelDrawData()->getTextureDiffuse()->getType().index);
    }
    if (modelGameObject->getModelDrawData()->getTextureSpecular() != nullptr && modelGameObject->getModelDrawData()->getUseTextureSpecular()) {
        modelGameObject->getModelDrawData()->getTextureSpecular()->bind(modelGameObject->getModelDrawData()->getTextureSpecular()->getType().index);
    }
    if (modelGameObject->getModelDrawData()->getTextureNormal() != nullptr && modelGameObject->getModelDrawData()->getUseTextureNormal()) {
        modelGameObject->getModelDrawData()->getTextureNormal()->bind(modelGameObject->getModelDrawData()->getTextureNormal()->getType().index);
    }
    if (modelGameObject->getModelDrawData()->getTextureHeight() != nullptr && modelGameObject->getModelDrawData()->getUseTextureHeight()) {
        modelGameObject->getModelDrawData()->getTextureHeight()->bind(modelGameObject->getModelDrawData()->getTextureHeight()->getType().index);
    }
    if (modelGameObject->getModelDrawData()->getTextureRoughness() != nullptr && modelGameObject->getModelDrawData()->getUseTextureRoughness()) {
        modelGameObject->getModelDrawData()->getTextureRoughness()->bind(modelGameObject->getModelDrawData()->getTextureRoughness()->getType().index);
    }
    if (modelGameObject->getModelDrawData()->getTextureShininess() != nullptr && modelGameObject->getModelDrawData()->getUseTextureShininess()) {
        modelGameObject->getModelDrawData()->getTextureShininess()->bind(modelGameObject->getModelDrawData()->getTextureShininess()->getType().index);
    }
    if (modelGameObject->getModelDrawData()->getTextureMetalness() != nullptr && modelGameObject->getModelDrawData()->getUseTextureMetalness()) {
        modelGameObject->getModelDrawData()->getTextureMetalness()->bind(modelGameObject->getModelDrawData()->getTextureMetalness()->getType().index);
    }
    if (modelGameObject->getModelDrawData()->getTextureAmbientOcclusion() != nullptr && modelGameObject->getModelDrawData()->getUseTextureAmbientOcclusion()) {
        modelGameObject->getModelDrawData()->getTextureAmbientOcclusion()->bind(modelGameObject->getModelDrawData()->getTextureAmbientOcclusion()->getType().index);
    }
    
    for (auto geometry : modelGameObject->getModelDrawData()->getMesh()->getGeometryList()) {
        geometry->getVertexArray()->bind();
        geometry->getVertexBuffer()->bind();
        if (geometry->getIsIndexed()) {
            geometry->getIndexBuffer()->bind();
            glDrawElements(GL_TRIANGLES, geometry->getRawIndexDataCount(), GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, geometry->getStructuredVertexDataCount());
        }
        geometry->getVertexArray()->unbind();
        geometry->getVertexBuffer()->unbind();
        geometry->getIndexBuffer()->unbind();
    }
    if (modelGameObject->getModelDrawData()->getShaderPhong() != nullptr) {
        modelGameObject->getModelDrawData()->getShaderPhong()->unbind();
    }
    else if (modelGameObject->getModelDrawData()->getShaderPbr() != nullptr) {
        modelGameObject->getModelDrawData()->getShaderPbr()->unbind();
    }
    //glDisable(GL_CULL_FACE);
}

void Renderer::drawLight(std::shared_ptr<LightGameObject> lightGameObject, std::shared_ptr<Camera> camera, bool scaled) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(lightGameObject->getPositionX(), lightGameObject->getPositionY(), lightGameObject->getPositionZ()));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(lightGameObject->getRotationX()), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(lightGameObject->getRotationY()), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(lightGameObject->getRotationZ()), glm::vec3(0.0f, 0.0f, 1.0f));
    if (!scaled) {
        modelMatrix = glm::scale(modelMatrix, glm::vec3(lightGameObject->getSizeX(), lightGameObject->getSizeY(), lightGameObject->getSizeZ()));
    }
    else {
        modelMatrix = glm::scale(modelMatrix, glm::vec3(lightGameObject->getScaledSizeX(), lightGameObject->getScaledSizeY(), lightGameObject->getScaledSizeZ()));
    }
    glm::mat4 inverseModelMatrix = glm::transpose(glm::inverse(modelMatrix));
    glm::mat4 viewMatrix = camera->getView();
    glm::mat4 projectionMatrix = camera->getProjection();

    lightGameObject->updateShaderViewData(modelMatrix, inverseModelMatrix, viewMatrix, projectionMatrix, camera->getPosition());
    lightGameObject->updateShaderColor();
    lightGameObject->updateShaderTime(glfwGetTime());
    lightGameObject->getLightDrawData()->getShader()->bind();
    for (auto geometry : lightGameObject->getLightDrawData()->getMesh()->getGeometryList()) {
        geometry->getVertexArray()->bind();
        geometry->getVertexBuffer()->bind();
        if (geometry->getIsIndexed()) {
            geometry->getIndexBuffer()->bind();
            glDrawElements(GL_TRIANGLES, geometry->getRawIndexDataCount(), GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, geometry->getStructuredVertexDataCount());
        }
        geometry->getVertexArray()->unbind();
        geometry->getVertexBuffer()->unbind();
        geometry->getIndexBuffer()->unbind();
    }
    lightGameObject->getLightDrawData()->getShader()->unbind();
}

void Renderer::drawSkybox(std::shared_ptr<Camera> camera) {
    glDisable(GL_CULL_FACE);
    std::shared_ptr<Skybox> skybox = ResourceManager::getInstance()->getSkyboxByName("skybox");
    glm::mat4 view = glm::mat4(glm::mat3(camera->getView()));
    glm::mat4 projection = camera->getProjection();
    skybox->getShader()->bind();
    skybox->getShader()->setMatrix4f("uView", view);
    skybox->getShader()->setMatrix4f("uProjection", projection);
    skybox->getShader()->setInt("uSkybox", 0);
    skybox->updateShaderColor();
    skybox->updateShaderTime(glfwGetTime());
    glDepthFunc(GL_LEQUAL);
    for (auto geometry : skybox->getMesh()->getGeometryList()) {
        geometry->getVertexArray()->bind();
        geometry->getVertexBuffer()->bind();
        skybox->getCubeMap()->bind(0);
        if (geometry->getIsIndexed()) {
            geometry->getIndexBuffer()->bind();
            glDrawElements(GL_TRIANGLES, geometry->getRawIndexDataCount(), GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, geometry->getStructuredVertexDataCount());
        }
        geometry->getVertexArray()->unbind();
        geometry->getVertexBuffer()->unbind();
        geometry->getIndexBuffer()->unbind();
    }
    skybox->getShader()->unbind();
    skybox->getCubeMap()->unbind();
    glDepthFunc(GL_LESS);

}

void Renderer::drawAll(std::shared_ptr<Camera> camera, bool scaled) {
    auto gameObjectList = GameObjectManager::getInstance()->getGameObjectList();
    for (auto gameObject : gameObjectList) {
        draw(gameObject, camera, scaled);
    }
}

void Renderer::drawAllModels(std::shared_ptr<Camera> camera, bool scaled) {
    auto modelGameObjectList = GameObjectManager::getInstance()->getModelGameObjectList();
    for (auto modelGameObject : modelGameObjectList) {
        drawModel(modelGameObject, camera, scaled);
    }
}


void Renderer::drawAllLights(std::shared_ptr<Camera> camera, bool scaled) {
    auto lightGameObjectList = GameObjectManager::getInstance()->getLightGameObjectList();
    for (auto lightGameObject : lightGameObjectList) {
        drawLight(lightGameObject, camera, scaled);
    }
}

void Renderer::colorBackground(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
