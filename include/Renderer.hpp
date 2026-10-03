#pragma once

#include "Util.hpp"
#include "DrawData.hpp"
#include "ModelDrawData.hpp"
#include "Camera.hpp"
#include "LightGameObject.hpp"
#include "Transform.hpp"
#include "Frustum.hpp"

class Renderer {
public:
	struct Stats {
		int drawCalls = 0;
		int instances = 0;
		int drawn = 0;
		int culled = 0;
	};

private:
	Renderer();
	~Renderer();
	static Renderer* instance;

	struct FrameContext {
		glm::mat4 view{ 1.0f };
		glm::mat4 projection{ 1.0f };
		glm::vec3 viewPos{ 0.0f };
		float time = 0.0f;
	};

	FrameContext frame;
	Frustum frustum;
	Stats stats;

	bool isVisible(const Transform& transform) const;

public:
	static Renderer* getInstance();

	void beginFrame(const Camera& camera);

	void draw(const std::shared_ptr<DrawData>& drawData, const Transform& transform, const Camera& camera);
	void drawModel(const std::shared_ptr<ModelDrawData>& modelDrawData, const Transform& transform, const Camera& camera);
	void drawLight(const std::shared_ptr<LightGameObject>& lightGameObject, const Camera& camera);
	void drawSkybox(const Camera& camera);

	void drawInstanced(const std::shared_ptr<DrawData>& drawData, const std::vector<const Transform*>& transforms, const Camera& camera);
	void drawInstancedModel(const std::shared_ptr<ModelDrawData>& modelDrawData, const std::vector<const Transform*>& transforms, const Camera& camera);

	void drawAll(const Camera& camera);
	void drawAllModels(const Camera& camera);
	void drawAllLights(const Camera& camera);

	void colorBackground(const glm::vec4& color);

	const Stats& getStats() const {
		return this->stats;
	}
};
