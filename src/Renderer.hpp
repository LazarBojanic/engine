#pragma once

#include "Util.hpp"
#include "GameObject.hpp"
#include "LightGameObject.hpp"
#include "Camera.hpp"
#include "ModelGameObject.hpp"
#include "Skybox.hpp"


class Renderer {
private:
	Renderer();
	~Renderer();
	static Renderer* instance;


public:
	static Renderer* getInstance();
	void draw(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Camera> camera, bool scaled);
	void drawModel(std::shared_ptr<ModelGameObject> modelGameObject, std::shared_ptr<Camera> camera, bool scaled);
	void drawLight(std::shared_ptr<LightGameObject> lightGameObject, std::shared_ptr<Camera> camera, bool scaled);
	void drawSkybox(std::shared_ptr<Camera> camera);
	void drawAll(std::shared_ptr<Camera> camera, bool scaled);
	void drawAllModels(std::shared_ptr<Camera> camera, bool scaled);
	void drawAllLights(std::shared_ptr<Camera> camera, bool scaled);
	void colorBackground(glm::vec4 color);
};
